const diff = require( 'diff' );
const fs = require( 'fs' ).promises;
const githubIssues = require( './githubIssues' );
const {
	fetchHttpStatusCodesList,
	httpStatusCodesFileName,
	httpStatusCodesFilePath
} = require( './httpStatusCodes' );

let log = console;

const issueTitleBase = 'IANA HTTP Status Code Update';

const checkForUpdate = async ( { github, core, context, dryRun } ) => {
	try
	{
		log = core;

		const httpStatusCodes = await fetchHttpStatusCodesList();
		const lastUpdatedDate = httpStatusCodes.lastUpdated;
		const diffWithLastUsedVersion = await getDiffWithLastUsedVersion( httpStatusCodes.httpStatusCodesList );
		if ( !diffWithLastUsedVersion ) {
			log.info( 'HTTP status codes list is still up to date' );
			return;
		}
		log.warning( 'HTTP status codes list is outdated!' );

		const existingGithubIssues = await githubIssues.searchForExistingGithubIssue( { keywords: [ issueTitleBase, lastUpdatedDate ], github, context } );

		if ( existingGithubIssues.total_count === 0 ) {
			createNewGithubIssue( { lastUpdatedDate, diffWithLastUsedVersion, github, context, dryRun } );
		}
		else if ( existingGithubIssues.total_count === 1 ) {
			log.info( 'An issue already exists for this update.' );
		}
		else {
			log.warning( `Multiple issues exist for the HTTP status code update from ${lastUpdatedDate}:\n${ JSON.stringify( existingGithubIssues, undefined, 4 ) }` );
		}
	}
	catch ( error ) {
		core.setFailed( `Could not check for HTTP status codes updates: ${error}` );
		throw error;
	}
};

const getDiffWithLastUsedVersion = async ( httpStatusCodeList ) => {
	const lastUsedVersion = await fs.readFile( httpStatusCodesFilePath, { encoding: 'utf-8' } );
	if ( lastUsedVersion === httpStatusCodeList ) {
		return null;
	}
	const patch = diff.createPatch( httpStatusCodesFileName, lastUsedVersion, httpStatusCodeList );
	return patch;
};

const createNewGithubIssue = async ( { lastUpdatedDate, diffWithLastUsedVersion, github, context, dryRun } ) => {
	const title = `${issueTitleBase} ${lastUpdatedDate}`;
	const body = `The HTTP status codes list has been updated on ${lastUpdatedDate}.    ` + '\n' +
				 'See https://www.iana.org/assignments/http-status-codes/http-status-codes.xhtml' + '\n\n' +
				 '## Diff ##'  + '\n' +
				 '```diff'  + '\n' +
				 diffWithLastUsedVersion + '\n' +
				 '```';

	 if ( dryRun ) {
		log.info( `Would create issue:\n${ JSON.stringify( { title, body }, null, 4 ) }` );
	}
	else {
		const newIssue = await githubIssues.createNewGithubIssue( { title, body, github, context } );
		log.info( `Created issue #${newIssue.number}: ${newIssue.html_url}`);
	}
};

const main = async () => {
	try
	{
		const httpStatusCodes = await fetchHttpStatusCodesList();
		log.log( httpStatusCodes.lastUpdated );
		const patch = await getDiffWithLastUsedVersion( httpStatusCodes.httpStatusCodesList );
		if ( patch ) {
			log.log( patch );
		}
	}
	catch( reason ) {
		log.error( reason );
		process.exitCode = -1;
	};
};

module.exports = checkForUpdate;

if ( require.main === module ) {
	main();
}
