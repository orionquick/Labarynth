// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Labarynth/Chunk.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeChunk() {}
// Cross Module References
	LABARYNTH_API UClass* Z_Construct_UClass_AChunk_NoRegister();
	LABARYNTH_API UClass* Z_Construct_UClass_AChunk();
	ENGINE_API UClass* Z_Construct_UClass_AActor();
	UPackage* Z_Construct_UPackage__Script_Labarynth();
// End Cross Module References
	void AChunk::StaticRegisterNativesAChunk()
	{
	}
	UClass* Z_Construct_UClass_AChunk_NoRegister()
	{
		return AChunk::StaticClass();
	}
	struct Z_Construct_UClass_AChunk_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_yIndex_MetaData[];
#endif
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_yIndex;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_xIndex_MetaData[];
#endif
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_xIndex;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_hash_MetaData[];
#endif
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_hash;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_AChunk_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AActor,
		(UObject* (*)())Z_Construct_UPackage__Script_Labarynth,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AChunk_Statics::Class_MetaDataParams[] = {
		{ "IncludePath", "Chunk.h" },
		{ "ModuleRelativePath", "Chunk.h" },
	};
#endif
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AChunk_Statics::NewProp_yIndex_MetaData[] = {
		{ "Category", "Chunk" },
		{ "ModuleRelativePath", "Chunk.h" },
		{ "ToolTip", "Y Component" },
	};
#endif
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UClass_AChunk_Statics::NewProp_yIndex = { "yIndex", nullptr, (EPropertyFlags)0x0010000000020001, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AChunk, yIndex), METADATA_PARAMS(Z_Construct_UClass_AChunk_Statics::NewProp_yIndex_MetaData, ARRAY_COUNT(Z_Construct_UClass_AChunk_Statics::NewProp_yIndex_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AChunk_Statics::NewProp_xIndex_MetaData[] = {
		{ "Category", "Chunk" },
		{ "ModuleRelativePath", "Chunk.h" },
		{ "ToolTip", "X component" },
	};
#endif
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UClass_AChunk_Statics::NewProp_xIndex = { "xIndex", nullptr, (EPropertyFlags)0x0010000000020001, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AChunk, xIndex), METADATA_PARAMS(Z_Construct_UClass_AChunk_Statics::NewProp_xIndex_MetaData, ARRAY_COUNT(Z_Construct_UClass_AChunk_Statics::NewProp_xIndex_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AChunk_Statics::NewProp_hash_MetaData[] = {
		{ "Category", "Chunk" },
		{ "ModuleRelativePath", "Chunk.h" },
		{ "ToolTip", "Used as a seed for random function to determine layout of chunk" },
	};
#endif
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UClass_AChunk_Statics::NewProp_hash = { "hash", nullptr, (EPropertyFlags)0x0010000000020001, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AChunk, hash), METADATA_PARAMS(Z_Construct_UClass_AChunk_Statics::NewProp_hash_MetaData, ARRAY_COUNT(Z_Construct_UClass_AChunk_Statics::NewProp_hash_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_AChunk_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AChunk_Statics::NewProp_yIndex,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AChunk_Statics::NewProp_xIndex,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AChunk_Statics::NewProp_hash,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_AChunk_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AChunk>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_AChunk_Statics::ClassParams = {
		&AChunk::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_AChunk_Statics::PropPointers,
		nullptr,
		ARRAY_COUNT(DependentSingletons),
		0,
		ARRAY_COUNT(Z_Construct_UClass_AChunk_Statics::PropPointers),
		0,
		0x009000A0u,
		METADATA_PARAMS(Z_Construct_UClass_AChunk_Statics::Class_MetaDataParams, ARRAY_COUNT(Z_Construct_UClass_AChunk_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_AChunk()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_AChunk_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(AChunk, 3379674584);
	template<> LABARYNTH_API UClass* StaticClass<AChunk>()
	{
		return AChunk::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_AChunk(Z_Construct_UClass_AChunk, &AChunk::StaticClass, TEXT("/Script/Labarynth"), TEXT("AChunk"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(AChunk);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
