const fetch = require( 'node-fetch' );
const diff = require( 'diff' );
const fs = require( 'fs' ).promises;
const path = require( 'path' );

let log = console;

const httpStatusCodesUrl = 'https://www.iana.org/assignments/http-status-codes/http-status-codes.txt';

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

		const existingGithubIssues = await searchForExistingGithubIssue( { lastUpdatedDate, github, context } );

		if ( existingGithubIssues.total_count === 0 ) {
			const newIssue = await createNewGithubIssue( { httpStatusCodes, diffWithLastUsedVersion, github, context, dryRun } );
			log.info( `Created issue #${newIssue.number}: ${newIssue.html_url}`);
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

const issueTitleBase = 'IANA HTTP Status Code Update';

const searchForExistingGithubIssue = async ( { lastUpdatedDate, github, context } ) => {
	const query = [ issueTitleBase, lastUpdatedDate, 'in:title', `repo:${context.payload.repository.full_name}`, 'type:issue' ].join( '+' );
	const searchResponse = await github.search.issuesAndPullRequests( {
		q: query,
	} );
	return searchResponse.data;
};

const createNewGithubIssue = async ( { httpStatusCodes, diffWithLastUsedVersion, github, context, dryRun } ) => {

	const newIssue = {
		owner: context.repo.owner,
		repo: context.repo.repo,
		title: `${issueTitleBase} ${httpStatusCodes.lastUpdated}`,
		body: `The HTTP status codes list has been updated on ${httpStatusCodes.lastUpdated}.    ` + '\n' +
		      'See https://www.iana.org/assignments/http-status-codes/http-status-codes.xhtml' + '\n\n' +
		      '## Diff ##'  + '\n' +
			  '```diff'  + '\n' +
			  diffWithLastUsedVersion + '\n' +
			  '```'
	};

	if ( dryRun ) {
		log.info( `Would create issue:\n${ JSON.stringify( newIssue, null, 4 ) }` );
		return { number: 0, html_url: context.payload.repository.issues_url };
	}

	const issueResponse = await github.issues.create( newIssue );
	return issueResponse.data;
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