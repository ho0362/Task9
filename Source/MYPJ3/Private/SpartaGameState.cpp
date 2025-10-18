/*#include "SpartaGameState.h"
#include "SpartaGameInstance.h"
#include "SpartaPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "SpawnVolume.h"
#include "CoinActor.h"
#include "Components/TextBlock.h"
#include "Blueprint/UserWidget.h"


ASpartaGameState::ASpartaGameState()
{
	Score = 0;
	SpawnedCoinCount = 0;
	CollectedCoinCount = 0;
	LevelDuration = 30.0f;
	CurrentLevelIndex = 0;
	MaxLevels = 3;
}

void ASpartaGameState::BeginPlay()
{
	Super::BeginPlay();

	StartLevel();

	GetWorldTimerManager().SetTimer(
		HUDUpdateTimerHandle,
		this,
		&ASpartaGameState::UpdateHUD,
		0.1f,
		true
	);
}
int32 ASpartaGameState::GetScore() const
{
	return Score;
}

void ASpartaGameState::AddScore(int32 Amount)
{
	if (UGameInstance* GameInstance = GetGameInstance())
	{
		USpartaGameInstance* SpartaGameInstance = Cast<USpartaGameInstance>(GameInstance);
		if (SpartaGameInstance)
		{
			SpartaGameInstance->AddToScore(Amount);
		}
	}
}

void ASpartaGameState::StartLevel()
{
	if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController())
	{
		if (ASpartaPlayerController* SpartaPlayerController = Cast <ASpartaPlayerController>(PlayerController))
		{
			SpartaPlayerController->ShowGameHUD();
		}
	}

	if (UGameInstance* GameInstance = GetGameInstance())
	{
		USpartaGameInstance* SpartaGameInstance = Cast<USpartaGameInstance>(GameInstance);
		if (SpartaGameInstance)
		{
			CurrentLevelIndex = SpartaGameInstance->CurrentLevelIndex;
		}
	}


	SpawnedCoinCount = 0;
	CollectedCoinCount = 0;

	TArray<AActor*> FoundVolumes;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASpawnVolume::StaticClass(), FoundVolumes);

	const int32 ItemToSpawn = 40;

	if (FoundVolumes.Num() > 0)
	{
		ASpawnVolume* SpawnVolume = Cast<ASpawnVolume>(FoundVolumes[0]);
		if (SpawnVolume)
		{
			for (int32 i = 0; i < ItemToSpawn; i++)
			{
				AActor* SpawnedActor = SpawnVolume->SpawnRandomItem();
				if (SpawnedActor && SpawnedActor->IsA(ACoinActor::StaticClass()))
				{
					SpawnedCoinCount++;
				}
			}
		}
	}



	GetWorldTimerManager().SetTimer(
		LevelTimerHandle,
		this,
		&ASpartaGameState::OnLevelTimeUp,
		LevelDuration,
		false
	);
}

void ASpartaGameState::OnLevelTimeUp()
{
	EndLevel();
}

void ASpartaGameState::OnCoinCollected()
{
	CollectedCoinCount++;

	UE_LOG(LogTemp, Warning, TEXT("Coin Collected: %d / %d"),
		CollectedCoinCount,
		SpawnedCoinCount);

	if (SpawnedCoinCount > 0 && CollectedCoinCount >= SpawnedCoinCount)
	{
		EndLevel();
	}
}
void ASpartaGameState::EndLevel()
{
	GetWorldTimerManager().ClearTimer(LevelTimerHandle);
	CurrentLevelIndex++;

	if (UGameInstance* GameInstance = GetGameInstance())
	{
		USpartaGameInstance* SpartaGameInstance = Cast<USpartaGameInstance>(GameInstance);
		if (SpartaGameInstance)
		{
			AddScore(Score);

			SpartaGameInstance->CurrentLevelIndex = CurrentLevelIndex;
		}
	}

	if (CurrentLevelIndex >= MaxLevels)
	{
		OnGameOver();
		return;
	}
	if (LevelMapNames.IsValidIndex(CurrentLevelIndex))
	{
		UGameplayStatics::OpenLevel(GetWorld(), LevelMapNames[CurrentLevelIndex]);
	}
	else
	{
		OnGameOver();
	}

}

void ASpartaGameState::OnGameOver()
{
	if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController())
	{
		if (ASpartaPlayerController* SpartaPlayerController = Cast <ASpartaPlayerController>(PlayerController))
		{
			SpartaPlayerController->SetPause(true);
			SpartaPlayerController->ShowMainMenu(true);
		}
	}

}

void ASpartaGameState::UpdateHUD()
{
	if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController())
	{
		if (ASpartaPlayerController* SpartaPlayerController = Cast<ASpartaPlayerController>(PlayerController))
		{
			if (UUserWidget* HUDWidget = SpartaPlayerController->GetHUDWidget())
			{
				if (UTextBlock* TimeText = Cast<UTextBlock>(HUDWidget->GetWidgetFromName(TEXT("Time"))))
				{
					float RemainingTime = GetWorldTimerManager().GetTimerRemaining(LevelTimerHandle);
					TimeText->SetText(FText::FromString(FString::Printf(TEXT("Time: %.1f"), RemainingTime)));
				}

				if (UTextBlock* ScoreText = Cast<UTextBlock>(HUDWidget->GetWidgetFromName(TEXT("Score"))))
				{
					if (UGameInstance* GameInstance = GetGameInstance())
					{
						USpartaGameInstance* SpartaGameInstance = Cast<USpartaGameInstance>(GameInstance);
						if (SpartaGameInstance)
						{
							ScoreText->SetText(FText::FromString(FString::Printf(TEXT("Score: %d"), SpartaGameInstance->TotalScore)));
						}
					}

				}

				if (UTextBlock* LevelIndexText = Cast<UTextBlock>(HUDWidget->GetWidgetFromName(TEXT("Level"))))
				{

					LevelIndexText->SetText(FText::FromString(FString::Printf(TEXT("Level: %d"), CurrentLevelIndex + 1)));
				}
			}
		}
	}
}*/

#include "SpartaGameState.h"
#include "SpartaGameInstance.h"
#include "SpartaPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "SpawnVolume.h"
#include "CoinActor.h"
#include "Components/TextBlock.h"
#include "Blueprint/UserWidget.h"

ASpartaGameState::ASpartaGameState()
{
	Score = 0;
	SpawnedCoinCount = 0;
	CollectedCoinCount = 0;

	LevelDuration = 30.0f;
	WaveDuration = 15.0f;

	CurrentLevelIndex = 0;
	MaxLevels = 3;

	CurrentWaveIndex = 0;
	MaxWaves = 3;
}

void ASpartaGameState::BeginPlay()
{
	Super::BeginPlay();

	StartLevel();

	GetWorldTimerManager().SetTimer(
		HUDUpdateTimerHandle,
		this,
		&ASpartaGameState::UpdateHUD,
		0.1f,
		true
	);
}

int32 ASpartaGameState::GetScore() const
{
	return Score;
}

void ASpartaGameState::AddScore(int32 Amount)
{
	if (UGameInstance* GameInstance = GetGameInstance())
	{
		if (USpartaGameInstance* SpartaGameInstance = Cast<USpartaGameInstance>(GameInstance))
		{
			SpartaGameInstance->AddToScore(Amount);
		}
	}
}

void ASpartaGameState::StartLevel()
{
	CurrentWaveIndex = 0;

	if (ASpartaPlayerController* SpartaPC = GetSpartaPlayerController())
	{
		SpartaPC->ShowGameHUD();
	}

	if (UGameInstance* GameInstance = GetGameInstance())
	{
		if (USpartaGameInstance* SpartaGameInstance = Cast<USpartaGameInstance>(GameInstance))
		{
			CurrentLevelIndex = SpartaGameInstance->CurrentLevelIndex;
		}
	}

	StartWave();
}

void ASpartaGameState::StartWave()
{
	// Wave 초기화
	SpawnedCoinCount = 0;
	CollectedCoinCount = 0;

	// 이전 Wave 아이템 제거
	for (AActor* Item : CurrentWaveItems)
	{
		if (Item && Item->IsValidLowLevelFast())
		{
			Item->Destroy();
		}
	}
	CurrentWaveItems.Empty();

	// 이번 Wave에 스폰할 아이템 개수
	int32 ItemToSpawn = (ItemsToSpawnPerWave.IsValidIndex(CurrentWaveIndex)) ? ItemsToSpawnPerWave[CurrentWaveIndex] : 20;

	if (ASpawnVolume* SpawnVolume = GetSpawnVolume())
	{
		for (int32 i = 0; i < ItemToSpawn; i++)
		{
			if (AActor* SpawnedActor = SpawnVolume->SpawnRandomItem())
			{
				if (SpawnedActor->IsA(ACoinActor::StaticClass()))
				{
					SpawnedCoinCount++;
				}

				CurrentWaveItems.Add(SpawnedActor);
			}
		}
	}

	// Wave별 환경 변화
	if (CurrentWaveIndex == 1)
	{
		EnableWave2();
	}
	else if (CurrentWaveIndex == 2)
	{
		EnableWave3();
	}

	// HUD Wave 알림
	if (ASpartaPlayerController* SpartaPC = GetSpartaPlayerController())
	{
		if (UUserWidget* HUDWidget = SpartaPC->GetHUDWidget())
		{
			UFunction* PlayAnimFunc = HUDWidget->FindFunction(FName("PlayShowWaveNotifyAnim"));
			if (PlayAnimFunc) HUDWidget->ProcessEvent(PlayAnimFunc, nullptr);

			if (UTextBlock* WaveNotifyText = Cast<UTextBlock>(HUDWidget->GetWidgetFromName("WaveNotifyText")))
			{
				WaveNotifyText->SetText(FText::FromString(FString::Printf(TEXT("Wave %d 발생!"), CurrentWaveIndex + 1)));
			}
		}
	}

	// Wave 타이머 시작
	GetWorldTimerManager().SetTimer(
		WaveTimerHandle,
		this,
		&ASpartaGameState::OnWaveTimeUp,
		WaveDuration,
		false
	);
}

void ASpartaGameState::OnWaveTimeUp()
{
	CurrentWaveIndex++;

	if (CurrentWaveIndex >= MaxWaves)
	{
		// Wave 종료 → Level 종료
		OnLevelTimeUp();
	}
	else
	{
		// 다음 Wave 시작
		StartWave();
	}
}

void ASpartaGameState::OnLevelTimeUp()
{
	EndLevel();
}

void ASpartaGameState::EndLevel()
{
	// Wave 타이머 클리어
	GetWorldTimerManager().ClearTimer(WaveTimerHandle);

	CurrentLevelIndex++;

	if (UGameInstance* GameInstance = GetGameInstance())
	{
		if (USpartaGameInstance* SpartaGameInstance = Cast<USpartaGameInstance>(GameInstance))
		{
			AddScore(Score);
			SpartaGameInstance->CurrentLevelIndex = CurrentLevelIndex;
		}
	}

	if (CurrentLevelIndex >= MaxLevels)
	{
		OnGameOver();
		return;
	}

	if (LevelMapNames.IsValidIndex(CurrentLevelIndex))
	{
		UGameplayStatics::OpenLevel(GetWorld(), LevelMapNames[CurrentLevelIndex]);
	}
	else
	{
		OnGameOver();
	}
}

void ASpartaGameState::OnGameOver()
{
	if (ASpartaPlayerController* SpartaPC = GetSpartaPlayerController())
	{
		SpartaPC->SetPause(true);
		SpartaPC->ShowMainMenu(true);
	}
}

void ASpartaGameState::OnCoinCollected()
{
	CollectedCoinCount++;

	UE_LOG(LogTemp, Warning, TEXT("Coin Collected: %d / %d"), CollectedCoinCount, SpawnedCoinCount);

	if (SpawnedCoinCount > 0 && CollectedCoinCount >= SpawnedCoinCount)
	{
		// Wave 종료
		GetWorldTimerManager().ClearTimer(WaveTimerHandle);
		OnWaveTimeUp();
	}
}

void ASpartaGameState::EnableWave2()
{
	const FString Msg = TEXT("Wave 2: Spawning and activating 5 Spike Traps!");
	UE_LOG(LogTemp, Warning, TEXT("%s"), *Msg);

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, Msg);
	}
}

void ASpartaGameState::EnableWave3()
{
	const FString Msg = TEXT("Wave 3: Spawning coins that orbit around!");
	UE_LOG(LogTemp, Warning, TEXT("%s"), *Msg);

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, Msg);
	}
}

void ASpartaGameState::UpdateHUD()
{
	if (ASpartaPlayerController* SpartaPC = GetSpartaPlayerController())
	{
		if (UUserWidget* HUDWidget = SpartaPC->GetHUDWidget())
		{
			// Time
			if (UTextBlock* TimeText = Cast<UTextBlock>(HUDWidget->GetWidgetFromName(TEXT("Time"))))
			{
				float RemainingTime = GetWorldTimerManager().GetTimerRemaining(WaveTimerHandle);
				TimeText->SetText(FText::FromString(FString::Printf(TEXT("Time: %.1f"), RemainingTime)));
			}

			// Score
			if (UTextBlock* ScoreText = Cast<UTextBlock>(HUDWidget->GetWidgetFromName(TEXT("Score"))))
			{
				if (UGameInstance* GameInstance = GetGameInstance())
				{
					if (USpartaGameInstance* SpartaGameInstance = Cast<USpartaGameInstance>(GameInstance))
					{
						ScoreText->SetText(FText::FromString(FString::Printf(TEXT("Score: %d"), SpartaGameInstance->TotalScore)));
					}
				}
			}

			// Level
			if (UTextBlock* LevelIndexText = Cast<UTextBlock>(HUDWidget->GetWidgetFromName(TEXT("Level"))))
			{
				LevelIndexText->SetText(FText::FromString(FString::Printf(TEXT("Level: %d"), CurrentLevelIndex + 1)));
			}
		}
	}
}

ASpartaPlayerController* ASpartaGameState::GetSpartaPlayerController() const
{
	if (APlayerController* PC = GetWorld()->GetFirstPlayerController())
	{
		return Cast<ASpartaPlayerController>(PC);
	}
	return nullptr;
}

ASpawnVolume* ASpartaGameState::GetSpawnVolume() const
{
	TArray<AActor*> FoundVolumes;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASpawnVolume::StaticClass(), FoundVolumes);

	if (FoundVolumes.Num() > 0)
	{
		return Cast<ASpawnVolume>(FoundVolumes[0]);
	}
	return nullptr;
}
