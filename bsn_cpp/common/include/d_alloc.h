#ifdef D_MemTrack


	#define D_Malloc(iAlloc, stSize) \
		iAlloc->MallocTrack( \
			stSize \
			, __FILE__ \
			, __FUNCTION__ \
			, __LINE__ \
		)


	#define D_Realloc(iAlloc, ptr, stSize) \
		iAlloc->ReallocTrack( \
			ptr \
			, stSize \
			, __FILE__ \
			, __FUNCTION__ \
			, __LINE__ \
		) 


	#define D_Free(iAlloc, ptr) \
		iAlloc->FreeTrack( \
			ptr \
			, __FILE__ \
			, __FUNCTION__ \
			, __LINE__ \
		); \
		ptr = nullptr 


#else


	#define D_Malloc(iAlloc, stSize) \
		iAlloc->Malloc( \
			stSize \
		) 


	#define D_Realloc(iAlloc, ptr, stSize) \
		iAlloc->Realloc( \
			ptr \
			, stSize \
		) 


	#define D_Free(iAlloc, ptr) \
		iAlloc->Free( \
			ptr \
		); \
		ptr = nullptr


#endif