const fetch = require( 'node-fetch' );
const path = require( 'path' );

const qNetworkReplyHeaderUrl = 'https://code.qt.io/cgit/qt/qtbase.git/plain/src/network/access/qnetworkreply.h';
const qNetworkReplyErrorCodesFileName = 'QNetworkReplyErrorCodes.txt';
const qNetworkReplyErrorCodesFilePath = path.join( __dirname, qNetworkReplyErrorCodesFileName );

const fetchQNetworkReplyErrorCodeListFromGitHub = async ( github ) => {
	const getContent = github.repos.getContent || github.repos.getContents;
	const response = await getContent( {
		owner: 'qt',
		repo: 'qtbase',
		path: 'src/network/access/qnetworkreply.h',
		ref: 'dev'
	} );
	const blobId = response.data.sha;

	const qNetworkReplyHeaderSource = decodeRepoContent( response.data );
	const qNetworkReplyErrorCodes = extractQNetworkReplyErrorCodes( qNetworkReplyHeaderSource );

	return { blobId, qNetworkReplyErrorCodes };
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
	const enumMatch = /enum NetworkError {(.*?)};/s.exec( qnetworkReplyHeaderSource );
	if ( !enumMatch ) {
		throw Error( 'Could not extract NetworkError codes from QNetworkReply header' );
	}
	const enums = enumMatch[ 1 ].trim().replace( /\/\/.*$|[ \t]+|\n\n+|,/mg, '' );
	return enums;
}

const fetchQNetworkReplyErrorCodeListFromQt = async () => {
	const response = await fetch( qNetworkReplyHeaderUrl );
	if ( !response.ok ) {
		throw Error( `Error fetching QNetworkReply header: ${response.status} ${response.statusText}` );
	}
	const qNetworkReplyHeaderSource = await response.text();

	return extractQNetworkReplyErrorCodes( qNetworkReplyHeaderSource );
}

module.exports = {
	fetchQNetworkReplyErrorCodeListFromGitHub,
	fetchQNetworkReplyErrorCodeListFromQt,
	qNetworkReplyErrorCodesFileName,
	qNetworkReplyErrorCodesFilePath
}
