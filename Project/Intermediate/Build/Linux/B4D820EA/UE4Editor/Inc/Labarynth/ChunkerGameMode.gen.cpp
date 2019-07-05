// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Labarynth/ChunkerGameMode.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeChunkerGameMode() {}
// Cross Module References
	LABARYNTH_API UClass* Z_Construct_UClass_AChunkerGameMode_NoRegister();
	LABARYNTH_API UClass* Z_Construct_UClass_AChunkerGameMode();
	ENGINE_API UClass* Z_Construct_UClass_AGameModeBase();
	UPackage* Z_Construct_UPackage__Script_Labarynth();
	LABARYNTH_API UClass* Z_Construct_UClass_AChunk_NoRegister();
	COREUOBJECT_API UClass* Z_Construct_UClass_UClass();
// End Cross Module References
	void AChunkerGameMode::StaticRegisterNativesAChunkerGameMode()
	{
	}
	UClass* Z_Construct_UClass_AChunkerGameMode_NoRegister()
	{
		return AChunkerGameMode::StaticClass();
	}
	struct Z_Construct_UClass_AChunkerGameMode_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_chunkClass_MetaData[];
#endif
		static const UE4CodeGen_Private::FClassPropertyParams NewProp_chunkClass;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_AChunkerGameMode_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AGameModeBase,
		(UObject* (*)())Z_Construct_UPackage__Script_Labarynth,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AChunkerGameMode_Statics::Class_MetaDataParams[] = {
		{ "HideCategories", "Info Rendering MovementReplication Replication Actor Input Movement Collision Rendering Utilities|Transformation" },
		{ "IncludePath", "ChunkerGameMode.h" },
		{ "ModuleRelativePath", "ChunkerGameMode.h" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
	};
#endif
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AChunkerGameMode_Statics::NewProp_chunkClass_MetaData[] = {
		{ "Category", "ChunkerGameMode" },
		{ "ModuleRelativePath", "ChunkerGameMode.h" },
	};
#endif
	const UE4CodeGen_Private::FClassPropertyParams Z_Construct_UClass_AChunkerGameMode_Statics::NewProp_chunkClass = { "chunkClass", nullptr, (EPropertyFlags)0x0014000000000001, UE4CodeGen_Private::EPropertyGenFlags::Class, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AChunkerGameMode, chunkClass), Z_Construct_UClass_AChunk_NoRegister, Z_Construct_UClass_UClass, METADATA_PARAMS(Z_Construct_UClass_AChunkerGameMode_Statics::NewProp_chunkClass_MetaData, ARRAY_COUNT(Z_Construct_UClass_AChunkerGameMode_Statics::NewProp_chunkClass_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_AChunkerGameMode_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AChunkerGameMode_Statics::NewProp_chunkClass,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_AChunkerGameMode_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AChunkerGameMode>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_AChunkerGameMode_Statics::ClassParams = {
		&AChunkerGameMode::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_AChunkerGameMode_Statics::PropPointers,
		nullptr,
		ARRAY_COUNT(DependentSingletons),
		0,
		ARRAY_COUNT(Z_Construct_UClass_AChunkerGameMode_Statics::PropPointers),
		0,
		0x009002A8u,
		METADATA_PARAMS(Z_Construct_UClass_AChunkerGameMode_Statics::Class_MetaDataParams, ARRAY_COUNT(Z_Construct_UClass_AChunkerGameMode_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_AChunkerGameMode()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_AChunkerGameMode_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(AChunkerGameMode, 3921208243);
	template<> LABARYNTH_API UClass* StaticClass<AChunkerGameMode>()
	{
		return AChunkerGameMode::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_AChunkerGameMode(Z_Construct_UClass_AChunkerGameMode, &AChunkerGameMode::StaticClass, TEXT("/Script/Labarynth"), TEXT("AChunkerGameMode"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(AChunkerGameMode);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
