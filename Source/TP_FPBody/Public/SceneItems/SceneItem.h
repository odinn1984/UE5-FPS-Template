#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SceneItem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBeginOverlapSignature, const AActor*, Actor);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEndOverlapSignature, const AActor*, Actor);

class UCapsuleComponent;
class UStaticMeshComponent;

UCLASS(Abstract)
class TP_FPBODY_API ASceneItem : public AActor
{
	GENERATED_BODY()
	
public:
	static FName CapsuleComponentName;
	static FName StaticMeshComponentName;

	UPROPERTY(BlueprintAssignable, Category = "Delegates")
	FOnBeginOverlapSignature OnBeginOverlap;

	UPROPERTY(BlueprintAssignable, Category = "Delegates")
  FOnEndOverlapSignature OnEndOverlap;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Settings")
	bool bShouldRotate = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Settings")
  FRotator RotationSpeed = FRotator(0.0f, 1.0f, 0.0f);

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Settings")
  bool bShouldDestroyOnEndOverlap = false;

	FORCEINLINE UCapsuleComponent* GetCapsule() const { return CapsuleComponent; }
	FORCEINLINE UStaticMeshComponent* GetMesh() const { return Mesh; }

	ASceneItem(const FObjectInitializer& ObjectInitializer);

	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintNativeEvent)
	void OnActorBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	virtual void OnActorBeginOverlap_Implementation(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(BlueprintNativeEvent)
  void OnActorEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
			UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	virtual void OnActorEndOverlap_Implementation(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collision", meta = (AllowPrivateAccess = "true"))
  TObjectPtr<UCapsuleComponent> CapsuleComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> Mesh;

};
