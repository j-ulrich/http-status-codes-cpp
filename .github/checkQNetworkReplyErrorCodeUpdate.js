const fetch = require( 'node-fetch' );
const diff = require( 'diff' );
const fs = require( 'fs' ).promises;
const path = require( 'path' );
const githubIssues = require( './githubIssues.js' );

let log = console;

const qNetworkReplyHeaderUrl = 'https://code.qt.io/cgit/qt/qtbase.git/plain/src/network/access/qnetworkreply.h';
const issueTitleBase = 'QNetworkReply Error Code Update';

const checkForUpdate = async ( { github, core, context, dryRun } ) => {
	try
	{
		log = core;

		const { commitId, qNetworkReplyErrorCodes } = await fetchQNetworkReplyErrorCodeListFromGitHub( github );
		const diffWithLastUsedVersion = await getDiffWithLastUsedVersion( qNetworkReplyErrorCodes );
		if ( !diffWithLastUsedVersion ) {
			log.info( 'QNetworkReply error codes list is still up to date' );
			return;
		}
		log.warning( 'QNetworkReply error codes list is outdated!' );

		const existingGithubIssues = await githubIssues.searchForExistingGithubIssue( { keywords: [ issueTitleBase, shortenCommitId( commitId ) ], github, context } );

		if ( existingGithubIssues.total_count === 0 ) {
			createNewGithubIssue( { commitId, diffWithLastUsedVersion, github, context, dryRun } );
		}
		else if ( existingGithubIssues.total_count === 1 ) {
			log.info( 'An issue already exists for this update.' );
		}
		else {
			log.warning( `Multiple issues exist for the QNetworkReply error codes update with id ${commitId}:\n${ JSON.stringify( existingGithubIssues, undefined, 4 ) }` );
		}
	}
	catch ( error ) {
		core.setFailed( `Could not check for HTTP status codes updates: ${error}` );
		throw error;
	}
};

const shortenCommitId = commitId => {
	return commitId.substring( 0, 6 )
};

const fetchQNetworkReplyErrorCodeListFromGitHub = async ( github ) => {
	const getContent = github.repos.getContent || github.repos.getContents;
	const response = await getContent( {
		owner: 'qt',
		repo: 'qtbase',
		path: 'src/network/access/qnetworkreply.h',
		ref: 'dev'
	} );
	const commitId = response.data.sha;

	const qNetworkReplyHeaderSource = decodeRepoContent( response.data );
	const qNetworkReplyErrorCodes = extractQNetworkReplyErrorCodes( qNetworkReplyHeaderSource );

	return { commitId, qNetworkReplyErrorCodes };
};

const fetchQNetworkReplyErrorCodeListFromQt = async () => {
	const response = await fetch( qNetworkReplyHeaderUrl );
	if ( !response.ok ) {
		throw Error( `Error fetching QNetworkReply header: ${response.status} ${response.statusText}` );
	}
	const qNetworkReplyHeaderSource = await response.text();

	return extractQNetworkReplyErrorCodes( qNetworkReplyHeaderSource );
}

const decodeRepoContent = ( response ) => {
	try {
		return Buffer.from( response.content, response.encoding ).toString( 'utf-8' );
	}
	catch( e ) {
		throw Error( `Unsupported repository content encoding: ${response.encoding}\nOriginal exception: ${e}` );
	}
};

const extractQNetworkReplyErrorCodes = ( qnetworkReplyHeaderSource ) => {
	const enumMatch = /enum NetworkError {(.*?)};/s.exec( qnetworkReplyHeaderSource );
	if ( !enumMatch ) {
		throw Error( 'Could not extract NetworkError codes from QNetworkReply header' );
	}
	const enums = enumMatch[ 1 ].trim().replace( /\/\/.*$|[ \t]+|\n\n+|,/mg, '' );
	return enums;
}

const getDiffWithLastUsedVersion = async ( qNetworkReplyErrorCodes ) => {
	const pathToLastUsedVersion = path.resolve( './.github/QNetworkReplyErroCodes.txt' );
	const lastUsedVersion = await fs.readFile( pathToLastUsedVersion, { encoding: 'utf-8' } );
	if ( lastUsedVersion === qNetworkReplyErrorCodes ) {
		return null;
	}
	const patch = diff.createPatch( 'QNetworkReplyErroCodes.txt', lastUsedVersion, qNetworkReplyErrorCodes );
	return patch;
};

const createNewGithubIssue = async ( { commitId, diffWithLastUsedVersion, github, context, dryRun } ) => {
	const commitIdShort = shortenCommitId( commitId );
	const title = `${issueTitleBase} ${commitIdShort}`;
	const body = 'The `QNetworkReply::NetworkError` codes list has been updated.    \n' +
				 `See [qnetworkreply.h@${commitIdShort}](https://code.qt.io/cgit/qt/qtbase.git/commit/src/network/access/qnetworkreply.h?id=${commitId})` + '\n\n' +
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
		const qnetworkReplyErrorCodes = await fetchQNetworkReplyErrorCodeListFromQt();
		const patch = await getDiffWithLastUsedVersion( qnetworkReplyErrorCodes );
		if ( patch ) {
			log.log( patch );
		}
		else {
			log.log( "Last used version is still up to date!" );
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