#define get_error(x) \
	if(!x) { \
		fprintf(stderr, "Error: %s\n", SDL_GetError()); \
		exit(-1); \
		}		
#define get_error_m(x, s) \
	if (!x) { \
		fprintf(stderr, "Error with %s: %s\n", s, SDL_GetError()); \
		exit(-1); \
	}
