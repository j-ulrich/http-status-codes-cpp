const fetch = require( 'node-fetch' );
const diff = require( 'diff' );
const fs = require( 'fs' ).promises;
const path = require( 'path' );

module.exports = ( { github, core } ) => {
	console.log( typeof fetch );
	console.log( typeof diff );
	console.log( typeof fs );
	console.log( typeof path );

	core.info( 'works' );
}