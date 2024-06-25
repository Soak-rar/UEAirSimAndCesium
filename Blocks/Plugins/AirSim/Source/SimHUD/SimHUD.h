#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "SimHUDWidget.h"
#include "SimMode/SimModeBase.h"
#include "PIPCamera.h"
#include "api/ApiServerBase.hpp"
#include <memory>
#include <vehicles/multirotor/api/MultirotorRpcLibClient.hpp>
#include "SimHUD.generated.h"

class UClientControlWidget;

using namespace msr::airlib;

UENUM(BlueprintType)
enum class ESimulatorMode : uint8
{
    SIM_MODE_HIL UMETA(DisplayName = "Hardware-in-loop")
};

UCLASS()
class AIRSIM_API ASimHUD : public AHUD
{
    GENERATED_BODY()

public:
    typedef msr::airlib::ImageCaptureBase::ImageType ImageType;
    typedef msr::airlib::AirSimSettings AirSimSettings;

public:
    void inputEventToggleRecording();
    void inputEventToggleReport();
    void inputEventToggleHelp();
    void inputEventToggleTrace();
    void inputEventToggleSubwindow0();
    void inputEventToggleSubwindow1();
    void inputEventToggleSubwindow2();
    void inputEventToggleAll();

    // 
    void createClientForThread();

    ASimHUD();
    virtual void BeginPlay() override;
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
    virtual void Tick(float DeltaSeconds) override;

protected:
    virtual void setupInputBindings();
    void toggleRecordHandler();
    void updateWidgetSubwindowVisibility();
    bool isWidgetSubwindowVisible(int window_index);
    void toggleSubwindowVisibility(int window_index);

private:
    void initializeSubWindows();
    void createSimMode();
    void initializeSettings();
    void setUnrealEngineSettings();
    void loadLevel();
    void createMainWidget();
    const std::vector<AirSimSettings::SubwindowSetting>& getSubWindowSettings() const;
    std::vector<AirSimSettings::SubwindowSetting>& getSubWindowSettings();

    bool getSettingsText(std::string& settingsText);
    bool getSettingsTextFromCommandLine(std::string& settingsText);
    bool readSettingsTextFromFile(const FString& fileName, std::string& settingsText);
    std::string getSimModeFromUser();

    static FString getLaunchPath(const std::string& filename);

    

    // 
    void createClientControlWidget();

private:
    typedef common_utils::Utils Utils;
    UClass* widget_class_;

    UPROPERTY()
    USimHUDWidget* widget_;
    UPROPERTY()
    ASimModeBase* simmode_;
    
    UClientControlWidget* client_control_widget;

    FRunnableThread* ClientThread;

    APIPCamera* subwindow_cameras_[AirSimSettings::kSubwindowCount];
    bool map_changed_;
};


class ClientRunable : public FRunnable
{
public:

    ClientRunable(FName name):client_name(name) {}
    virtual bool Init() override
    {
        client = new MultirotorRpcLibClient();
        if (client)
        {
            return true;
        }
        return false;
    }

    virtual uint32 Run() override;

    virtual void Stop() override;

    virtual void Exit() override;

    virtual ~ClientRunable() {}

private:
    
    MultirotorRpcLibClient* client;

    FName client_name;

    TWeakPtr<ASimHUD> sim_HUD;


        
};