// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ArduinoKitPCH.h"

class FArduinoKitThread : public FRunnable
{
public:
		static FArduinoKitThread * Runnable;
		FRunnableThread* Thread;
		FThreadSafeCounter StopTaskCounter;
		TArray<FString> StringStack;
		TArray<uint8> Buffer;
		int32 StringStackSize;
		
		FArduinoKitThread(int32 StringStackSize);
		virtual ~FArduinoKitThread();
		
		virtual bool Init();
		virtual uint32 Run();
		virtual void Stop();

		void EnsureCompletion();

		static FArduinoKitThread* Launch(int32 StringStackSize);
		static void Shutdown();
};
