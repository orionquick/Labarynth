// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef LABARYNTH_Chunk_generated_h
#error "Chunk.generated.h already included, missing '#pragma once' in Chunk.h"
#endif
#define LABARYNTH_Chunk_generated_h

#define Project_Source_Labarynth_Chunk_h_165_RPC_WRAPPERS
#define Project_Source_Labarynth_Chunk_h_165_RPC_WRAPPERS_NO_PURE_DECLS
#define Project_Source_Labarynth_Chunk_h_165_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesAChunk(); \
	friend struct Z_Construct_UClass_AChunk_Statics; \
public: \
	DECLARE_CLASS(AChunk, AActor, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/Labarynth"), NO_API) \
	DECLARE_SERIALIZER(AChunk)


#define Project_Source_Labarynth_Chunk_h_165_INCLASS \
private: \
	static void StaticRegisterNativesAChunk(); \
	friend struct Z_Construct_UClass_AChunk_Statics; \
public: \
	DECLARE_CLASS(AChunk, AActor, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/Labarynth"), NO_API) \
	DECLARE_SERIALIZER(AChunk)


#define Project_Source_Labarynth_Chunk_h_165_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API AChunk(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(AChunk) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AChunk); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AChunk); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API AChunk(AChunk&&); \
	NO_API AChunk(const AChunk&); \
public:


#define Project_Source_Labarynth_Chunk_h_165_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API AChunk(AChunk&&); \
	NO_API AChunk(const AChunk&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AChunk); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AChunk); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(AChunk)


#define Project_Source_Labarynth_Chunk_h_165_PRIVATE_PROPERTY_OFFSET
#define Project_Source_Labarynth_Chunk_h_162_PROLOG
#define Project_Source_Labarynth_Chunk_h_165_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	Project_Source_Labarynth_Chunk_h_165_PRIVATE_PROPERTY_OFFSET \
	Project_Source_Labarynth_Chunk_h_165_RPC_WRAPPERS \
	Project_Source_Labarynth_Chunk_h_165_INCLASS \
	Project_Source_Labarynth_Chunk_h_165_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define Project_Source_Labarynth_Chunk_h_165_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	Project_Source_Labarynth_Chunk_h_165_PRIVATE_PROPERTY_OFFSET \
	Project_Source_Labarynth_Chunk_h_165_RPC_WRAPPERS_NO_PURE_DECLS \
	Project_Source_Labarynth_Chunk_h_165_INCLASS_NO_PURE_DECLS \
	Project_Source_Labarynth_Chunk_h_165_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> LABARYNTH_API UClass* StaticClass<class AChunk>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID Project_Source_Labarynth_Chunk_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
