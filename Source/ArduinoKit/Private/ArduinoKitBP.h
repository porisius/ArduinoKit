#pragma once

#include "ArduinoKitPCH.h"
#include "ArduinoKitBP.generated.h"

UCLASS(Blueprintable)
class UArduinoKitBP : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()		

public:
	UArduinoKitBP(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable, Category = "ArduinoKit")
		static void Open(FString port, int32 baudrate, int32 TextStackSize = 50);

	UFUNCTION(BlueprintCallable, Category = "ArduinoKit")
		static void Close();

	UFUNCTION(BlueprintCallable, Category = "ArduinoKit")
		static void WriteBytes(TArray<uint8> BinaryData);

	UFUNCTION(BlueprintCallable, Category = "ArduinoKit")
		static void WriteText(FString text);

//	UFUNCTION(BlueprintCallable, Category = "ArduinoKit")
		static TArray<uint8> ReadBytes();
	
	UFUNCTION(BlueprintCallable, Category = "ArduinoKit")
		static FString ReadText();

	UFUNCTION(BlueprintCallable, Category = "ArduinoKit")
		static TArray<FString> GetAllAvailableTexts();

	UFUNCTION(BlueprintCallable, Category = "ArduinoKit")
		static bool IsOpen();

//	UFUNCTION(BlueprintCallable, Category = "ArduinoKit")
		static FString StringFromByteArray(TArray<uint8> BinaryData);
};

