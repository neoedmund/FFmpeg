static char hasLyrics = 0 ;
static double lyrics_seek = 0 ;
void lyrics_seeked ( void ) ;
double lyrics_process ( double sec ) ;
char lyrics_open ( const char * input_filename ) ;
void lyrics_finished ( void ) ;

// ---- impl
// ---- textfrog declare
typedef struct textfrog_s {
	int env ;
} * textfrog ;

# ifdef __cplusplus
extern "C" {
	# endif
	# define TFG_API
	TFG_API textfrog tfg_init ( int debug ) ;
	TFG_API int tfg_include ( textfrog tfg , const char * fn ) ;
	TFG_API int64_t * tfg_call ( textfrog tfg , const char * func , int argc , ... ) ;
	TFG_API int64_t * tfg_call2 ( textfrog tfg , const char * func , const char * paramSig , ... ) ;
	TFG_API int64_t * tfg_calljava ( textfrog tfg , const char * clz , const char * func , const char * paramSig , ... ) ;
	TFG_API void tfg_flushLog ( ) ;
	TFG_API int detectJvm ( ) ;
	# ifdef __cplusplus
}
# endif
static textfrog tfg_inst = 0 ;
// -----impl lyrics
void lyrics_seeked ( void ) {
	if ( tfg_inst == 0 ) return ;
	tfg_call ( tfg_inst , "lyrics_seeked" , 0 ) ;
}
double lyrics_process ( double sec ) {
	if ( tfg_inst == 0 ) return 0 ;
	int64_t v = tfg_call2 ( tfg_inst , "lyrics_process" , "D" , sec ) ;
	return v / 1000.0d ;
}
char lyrics_open ( const char * input_filename ) {
	if ( tfg_inst == 0 ) {
		tfg_inst = tfg_init ( 1 ) ;
		tfg_include ( tfg_inst , "lyrics.tfg" ) ;
	}
	if ( tfg_inst == 0 ) {
		printf ( "tfg_inst init seem failed\n" ) ;
		return 0 ;
	}
	return ( char ) tfg_call2 ( tfg_inst , "lyrics_open" , "S" , input_filename ) ;
}
void lyrics_finished ( void ) {
	if ( tfg_inst == 0 ) return ;
	tfg_call ( tfg_inst , "lyrics_finished" , 0 ) ;
}
