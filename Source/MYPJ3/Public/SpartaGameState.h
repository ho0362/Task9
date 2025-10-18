

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "SpartaGameState.generated.h"

UCLASS()
class MYPJ3_API ASpartaGameState : public AGameState
{
	GENERATED_BODY()

public:
	ASpartaGameState();

	virtual void BeginPlay() override;

	// Score
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Score")
	int32 Score;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Coin")
	int32 SpawnedCoinCount;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Coin")
	int32 CollectedCoinCount;

	// Level
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level")
	float LevelDuration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level")
	float WaveDuration;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Level")
	int32 CurrentLevelIndex;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Level")
	int32 MaxLevels;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level")
	TArray<FName> LevelMapNames;

	// Wave
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Wave")
	int32 CurrentWaveIndex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wave")
	int32 MaxWaves;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wave")
	TArray<int32> ItemsToSpawnPerWave;

	UPROPERTY()
	TArray<AActor*> CurrentWaveItems;

	// Timer handles
	FTimerHandle LevelTimerHandle;
	FTimerHandle WaveTimerHandle;
	FTimerHandle HUDUpdateTimerHandle;

	// Score functions
	UFUNCTION(BlueprintPure, Category = "Score")
	int32 GetScore() const;

	UFUNCTION(BlueprintCallable, Category = "Score")
	void AddScore(int32 Amount);

	// Level & Wave functions
	UFUNCTION(BlueprintCallable, Category = "Level")
	void StartLevel();

	void StartWave();
	void OnWaveTimeUp();
	void OnLevelTimeUp();
	void EndLevel();
	void OnCoinCollected();

	UFUNCTION(BlueprintCallable, Category = "Level")
	void OnGameOver();

	// Wave specific
	void EnableWave2();
	void EnableWave3();

	// HUD
	void UpdateHUD();

private:
	class ASpartaPlayerController* GetSpartaPlayerController() const;
	class ASpawnVolume* GetSpawnVolume() const;
};
