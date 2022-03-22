const diff = require( 'diff' );
const fs = require( 'fs' ).promises;
const githubIssues = require( './githubIssues' );
const {
	fetchQNetworkReplyErrorCodeListFromGitHub,
	fetchQNetworkReplyErrorCodeListFromQt,
	qNetworkReplyErrorCodesFilePath,
	qNetworkReplyErrorCodesFileName
} = require('./qNetworkReplyErrorCodes');

let log = console;

const issueTitleBase = 'QNetworkReply Error Code Update';

const checkForUpdate = async ( { github, core, context, dryRun } ) => {
	try
	{
		log = core;

		const { blobId, qNetworkReplyErrorCodes } = await fetchQNetworkReplyErrorCodeListFromGitHub( github );
		const blobIdShort = shortenId( blobId );
		const diffWithLastUsedVersion = await getDiffWithLastUsedVersion( qNetworkReplyErrorCodes );
		if ( !diffWithLastUsedVersion ) {
			log.info( 'QNetworkReply error codes list is still up to date' );
			return;
		}
		log.warning( 'QNetworkReply error codes list is outdated!' );

		const existingGithubIssues = await githubIssues.searchForExistingGithubIssue( { keywords: [ issueTitleBase, blobIdShort ], github, context } );

		if ( existingGithubIssues.total_count === 0 ) {
			createNewGithubIssue( { blobId, diffWithLastUsedVersion, github, context, dryRun } );
		}
		else if ( existingGithubIssues.total_count === 1 ) {
			log.info( 'An issue already exists for this update.' );
		}
		else {
			log.warning( `Multiple issues exist for the QNetworkReply error codes update with id ${blobIdShort}:\n${ JSON.stringify( existingGithubIssues, undefined, 4 ) }` );
		}
	}
	catch ( error ) {
		core.setFailed( `Could not check for HTTP status codes updates: ${error}` );
		throw error;
	}
};

const shortenId = id => {
	return id.substring( 0, 8 )
};


const getDiffWithLastUsedVersion = async ( qNetworkReplyErrorCodes ) => {
	const pathToLastUsedVersion = qNetworkReplyErrorCodesFilePath;
	const lastUsedVersion = await fs.readFile( pathToLastUsedVersion, { encoding: 'utf-8' } );
	if ( lastUsedVersion === qNetworkReplyErrorCodes ) {
		return null;
	}
	const patch = diff.createPatch( qNetworkReplyErrorCodesFileName, lastUsedVersion, qNetworkReplyErrorCodes );
	return patch;
};

const createNewGithubIssue = async ( { blobId, diffWithLastUsedVersion, github, context, dryRun } ) => {
	const blobIdShort = shortenId( blobId );
	const title = `${issueTitleBase} ${blobIdShort}`;
	const body = 'The `QNetworkReply::NetworkError` codes list has been updated.    \n' +
				 'See https://code.qt.io/cgit/qt/qtbase.git/log/src/network/access/qnetworkreply.h' + '\n\n' +
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
		const qNetworkReplyErrorCodes = await fetchQNetworkReplyErrorCodeListFromQt();
		const patch = await getDiffWithLastUsedVersion( qNetworkReplyErrorCodes );
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
