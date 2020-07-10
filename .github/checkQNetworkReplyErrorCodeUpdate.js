const diff = require( 'diff' );
const fs = require( 'fs' ).promises;
const path = require( 'path' );
const githubIssues = require( './githubIssues.js' );

let log = console;

const qnetworkReplyHeaderUrl = 'https://code.qt.io/cgit/qt/qtbase.git/plain/src/network/access/qnetworkreply.h';
const issueTitleBase = 'QNetworkReply Error Code Update';

const checkForUpdate = async ( { github, core, context, dryRun } ) => {
	try
	{
		log = core;

		const qnetworkReplyErrorCodes = await fetchQNetworkReplyErrorCodeList( github );
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

const fetchQNetworkReplyErrorCodeList = async ( github ) => {

	const response = await github.repos.getContent( {
		owner: 'qt',
		repo: 'qtbase',
		path: 'src/network/access/qnetworkreply.h',
		ref: 'dev'
	} );
	const commitId = response.sha;

	const qnetworkReplyHeaderSource = decodeRepoContent( response );
	const qnetworkReplyErrorCodes = extractQNetworkReplyErrorCodes( qnetworkReplyHeaderSource );

	return { commitId, qnetworkReplyErrorCodes };
};

const decodeRepoContent = ( response ) => {
	try {
		return Buffer.from( response.content, response.encoding ).toString( 'utf-8' );
	}
	catch( e ) {
		throw Error( `Unsupported repository content encoding: ${response.encoding}\nOriginal exception: ${e}` );
	}
};

const extractQNetworkReplyErrorCodes = ( qnetworkReplyHeaderSource ) => {
	
}

const getDiffWithLastUsedVersion = async ( httpStatusCodeList ) => {
	const pathToLastUsedVersion = path.resolve( './.github/http-status-codes.txt' );
	const lastUsedVersion = await fs.readFile( pathToLastUsedVersion, { encoding: 'utf-8' } );
	if ( lastUsedVersion === httpStatusCodeList ) {
		return null;
	}
	const patch = diff.createPatch( 'http-status-codes.txt', lastUsedVersion, httpStatusCodeList );
	return patch;
};

const createNewGithubIssue = async ( { diffWithLastUsedVersion, github, context, dryRun } ) => {
	const title = `${issueTitleBase} ${lastUpdatedDate}`;
	const body = 'The `QNetworkReply::NetworkError` codes list has been updated.    \n' +
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
		const qnetworkReplyErrorCodes = await fetchQNetworkReplyErrorCodeList();
		const patch = await getDiffWithLastUsedVersion( qnetworkReplyErrorCodes );
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