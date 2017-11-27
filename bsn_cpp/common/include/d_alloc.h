#pragma once

#ifdef D_MemTrack


	#define D_Malloc(iAlloc, stSize) \
	if (iAlloc != nullptr) \
	{ \
		iAlloc->Malloc( \
			stSize \
			, __FILE__ \
			, __FUNCTION__ \
			, __LINE__ \
		); \
	} \
	else \
	{ \
		return nullptr; \
	}


	#define D_Realloc(iAlloc, ptr, stSize) \
	if (iAlloc != nullptr) \
	{ \
		iAlloc->Realloc( \
			ptr \
			, stSize \
			, __FILE__ \
			, __FUNCTION__ \
			, __LINE__ \
		); \
	} \
	else \
	{ \
		return nullptr; \
	}


	#define D_Free(iAlloc, ptr) \
	if (iAlloc != nullptr) \
	{ \
		iAlloc->Free( \
			ptr \
			, __FILE__ \
			, __FUNCTION__ \
			, __LINE__ \
		); \
		ptr = nullptr; \
	} \
	else \
	{ \
		return; \
	}


#else


	#define D_Malloc(iAlloc, stSize) \
	if (iAlloc != nullptr) \
	{ \
		iAlloc->MallocTrack( \
			stSize \
		); \
	} \
	else \
	{ \
		return nullptr; \
	}


	#define D_Realloc(iAlloc, ptr, stSize) \
	if (iAlloc != nullptr) \
	{ \
		iAlloc->ReallocTrack( \
			ptr \
			, stSize \
		); \
	} \
	else \
	{ \
		return nullptr; \
	}


	#define D_Free(iAlloc, ptr) \
	if (iAlloc != nullptr) \
	{ \
		iAlloc->FreeTrack( \
			ptr \
		); \
		ptr = nullptr; \
	} \
	else \
	{ \
		return; \
	}


#endif