#include "ArduinoKitBP.h"
#include "ArduinoKitPCH.h"



#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#include "rs232.h"

#include "ArduinoKitThread.h"

UArduinoKitBP::UArduinoKitBP(const class FObjectInitializer& PCIP)
	: Super(PCIP)
{
}

void UArduinoKitBP::Open(FString port, int32 baudrate, int32 TextStackSize)
{
	Close();

	if (RS232_OpenComportUE4(TCHAR_TO_ANSI(*port), baudrate))
	{
		UE_LOG(LogTemp, Warning, TEXT("UArduinoKitBP::Open -> Failed"));
		FArduinoKitThread::Shutdown();
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("UArduinoKitBP::Open -> Success"));
		FArduinoKitThread::Launch(TextStackSize);
	}
	
}

void UArduinoKitBP::Close()
{
	if (RS232_CloseComportUE4()) {
		UE_LOG(LogTemp, Warning, TEXT("UArduinoKitBP::Close -> Failed"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("UArduinoKitBP::Close -> Success"));
	}
	FArduinoKitThread::Shutdown();
}

void UArduinoKitBP::WriteBytes(TArray<uint8> binaryData)
{
	if (RS232_IsOpenUE4()) {
		unsigned char * data = reinterpret_cast<unsigned char*>(binaryData.GetData());

		RS232_SendBufUE4(data, binaryData.Num());
	}
}

void UArduinoKitBP::WriteText(FString text)
{
	if (RS232_IsOpenUE4()) {
		FBufferArchive BinaryArrayArchive;
		BinaryArrayArchive << text;

		WriteBytes(BinaryArrayArchive);
	}
}


TArray<uint8> UArduinoKitBP::ReadBytes()
{
	TArray<uint8> ReturnBytes;
	if (RS232_IsOpenUE4()) {		
		unsigned char buf[4096];
		int32 n;
		n = RS232_PollComportUE4(buf, 4095);
		if (n > 0)
		{
			for (int32 x = 0; x < n; x++) {
				ReturnBytes.Add(buf[x]);
			}
		}
	}
	return ReturnBytes;
}


FString UArduinoKitBP::ReadText()
{
	if (FArduinoKitThread::Runnable != nullptr && FArduinoKitThread::Runnable->StringStack.Num()>0) {
		FString readText = FArduinoKitThread::Runnable->StringStack.Pop();
		return readText;
	}

	return FString();
}

TArray<FString> UArduinoKitBP::GetAllAvailableTexts()
{
	if (FArduinoKitThread::Runnable->StringStack.Num() > 0) {
		TArray<FString> texts = FArduinoKitThread::Runnable->StringStack;
		FArduinoKitThread::Runnable->StringStack.Empty();
		return texts;
	}

	return TArray<FString>();
}


bool UArduinoKitBP::IsOpen()
{
	if (RS232_IsOpenUE4() != 0) {
		return true;
	}
	else {
		return false;
	}	
}

FString UArduinoKitBP::StringFromByteArray(TArray<uint8> BinaryData)
{
	const std::string str_converted(reinterpret_cast<const char*>(BinaryData.GetData()), BinaryData.Num());

	return FString(str_converted.c_str());
}

