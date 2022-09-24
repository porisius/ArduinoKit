// Fill out your copyright notice in the Description page of Project Settings.

#include "ArduinoKitThread.h"
#include "ArduinoKitBP.h"
#include "ArduinoKitPCH.h"

FArduinoKitThread* FArduinoKitThread::Runnable = NULL;

FArduinoKitThread::FArduinoKitThread(int32 StringStackSize)
{
	this->StringStackSize = StringStackSize;
	Thread = FRunnableThread::Create(this, TEXT("FArduinoKitThread"), 0, TPri_BelowNormal);
}

FArduinoKitThread::~FArduinoKitThread()
{
	delete Thread;
	Thread = NULL;
}


//Init
bool FArduinoKitThread::Init()
{
	return true;
}

//Run
uint32 FArduinoKitThread::Run()
{
	FPlatformProcess::Sleep(0.03);

	while (StopTaskCounter.GetValue() == 0 && UArduinoKitBP::IsOpen())
	{
		TArray<uint8> readBytes = UArduinoKitBP::ReadBytes();

		for (int32 x = 0; x < readBytes.Num(); x++) {
			uint8 readByte = readBytes[x];
			if (readByte == 10) { // readByte == /n

				if (StringStack.Num() >= StringStackSize) {
					StringStack.RemoveAt(0);
				}


				const std::string str_converted(reinterpret_cast<const char*>(Buffer.GetData()), Buffer.Num());

				StringStack.Add(FString(str_converted.c_str()));

				Buffer.Empty();

				//UE_LOG(LogTemp, Warning, TEXT("FArduinoKitThread::Run Stack Size: %d"), StringStack.Num());
			}
			else {
				Buffer.Add(readByte);
			}
		}

		FPlatformProcess::Sleep(0.03);
		

		
	}
	return 0;
}

void FArduinoKitThread::Stop()
{
	StopTaskCounter.Increment();
}

void FArduinoKitThread::EnsureCompletion()
{
	Stop();
	Thread->WaitForCompletion();
}

FArduinoKitThread* FArduinoKitThread::Launch(int32 StringStackSize)
{
	//Create new instance of thread if it does not exist
	//		and the platform supports multi threading!
	if (!Runnable && FPlatformProcess::SupportsMultithreading())
	{
		Runnable = new FArduinoKitThread(StringStackSize);
	}
	return Runnable;
}

void FArduinoKitThread::Shutdown()
{
	if (Runnable)
	{
		Runnable->EnsureCompletion();
		delete Runnable;
		Runnable = NULL;
	}
}

