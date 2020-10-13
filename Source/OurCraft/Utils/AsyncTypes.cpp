// Fill out your copyright notice in the Description page of Project Settings.


#include "AsyncTypes.h"

FGenerationAsyncTask::FGenerationAsyncTask(FGenerationTaskWork* Work, FGenerationTaskComplete* CallBack, FGenerationAsyncResult* ObjectForContainsResults) {
	WorkDelegate = Work;
	CallBackDelegate = CallBack;
	ResultData = ObjectForContainsResults;
}

void FGenerationAsyncTask::DoWork() {

	if (WorkDelegate->IsBound()) {
		//Executing async work
		WorkDelegate->Execute(ResultData);
	}
	if (CallBackDelegate->IsBound()) {
		//Work is complete, callback to GameThread
		AsyncTask(ENamedThreads::GameThread, [this] {CallBackDelegate->Execute(ResultData); });
	}
}

TStatId FGenerationAsyncTask::GetStatId() const {
	RETURN_QUICK_DECLARE_CYCLE_STAT(FGenerationAsyncTask, STATGROUP_ThreadPoolAsyncTasks);
}

