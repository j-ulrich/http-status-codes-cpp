const fetch = require( 'node-fetch' );
const diff = require( 'diff' );
const fs = require( 'fs' ).promises;
const path = require( 'path' );
const githubIssues = require( './githubIssues.js' );

let log = console;

const httpStatusCodesUrl = 'https://www.iana.org/assignments/http-status-codes/http-status-codes.txt';
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

const fetchHttpStatusCodesList = async () => {
	const response = await fetch( httpStatusCodesUrl );
	if ( !response.ok ) {
		throw Error( `Error fetching HTTP status codes list: ${response.status} ${response.statusText}` );
	}
	const httpStatusCodesList = await response.text();

	const match = /Last Updated\s+(\d{4}-\d{2}-\d{2})/.exec( httpStatusCodesList );
	if ( !match ) {
		throw Error( 'Could not find "Last Updated" date in HTTP status list' );
	}
	const lastUpdated = match[ 1 ];
	return { lastUpdated, httpStatusCodesList };
};

const getDiffWithLastUsedVersion = async ( httpStatusCodeList ) => {
	const pathToLastUsedVersion = path.resolve( './.github/http-status-codes.txt' );
	const lastUsedVersion = await fs.readFile( pathToLastUsedVersion, { encoding: 'utf-8' } );
	if ( lastUsedVersion === httpStatusCodeList ) {
		return null;
	}
	const patch = diff.createPatch( 'http-status-codes.txt', lastUsedVersion, httpStatusCodeList );
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