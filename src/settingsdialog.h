#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include "gui.h"
#include "gridlayout.h"

#include <string>
#include <vector>
#include <algorithm>

struct ScreenMode
{
    ScreenMode(int w, int h, int f) :
        width(w), height(h), fullscreen(f)
    {
    }
    int width;
    int height;
    int fullscreen;

    bool operator<(const ScreenMode& other) const
    {
        if (width < other.width)
            return true;
        if (width > other.width)
            return false;
        if (height < other.height)
            return true;
        if (height > other.height)
            return false;
        if (fullscreen < other.fullscreen)
            return true;
        return false;
    }

    bool operator==(const ScreenMode& other) const
    {
        return width == other.width && height == other.height && fullscreen == other.fullscreen;
    }

    std::string getAspectRatioString() const
    {
        int ratioWs[] = {5,4,16,16};
        int ratioHs[] = {4,3,10,9};
        for (int i = 0; i != 4; ++i)
        {
            if (width * ratioHs[i] == height * ratioWs[i])
            {
                char buff[64] = {0};
                snprintf(buff, 63, "(%d:%d) ", ratioWs[i], ratioHs[i]);
                return buff;
            }
        }
        return "";
    }
};

class SettingsDialog : public GuiDialog
{
public:
    SettingsDialog(const std::vector<ScreenMode>& screenModes, ScreenMode currentScreenModeIndex, ScreenMode defaultScreenModeIndex, bool currentVsyncState, int currentAntialiasingMode, int currentTextureFilter, bool currentFpsState,
        const std::vector<std::string>& openalDevices, const char* currentOpenalDevice
        );

    virtual void onQuit();

    virtual void onButton(int itemIndex);

    virtual void onKeyDown(SDLKey k);

    virtual void onKeyUp(SDLKey k);

    int getSelectedScreenMode() const;
    bool getVsyncChecked() const;

    int getAntialiasingMode() const;
    int getTextureFilter() const;

    bool getShowFpsChecked() const;

    const char* getOpenalDevice() const;

    bool m_continue; // pokračovat v programu?

private:
    GridLayout m_layout;

    std::vector<std::string> m_openalDevices;

    int m_defaultScreenModeIndex;

    // gui item indices
    int m_resolutionsComboIndex;
    int m_vsyncIndex;

    int m_antialiasingIndex;
    int m_textureFilterIndex;

    int m_showFpsIndex;
    int m_audioDevicesComboIndex;

    int m_okButtonIndex;
    int m_cancelButtonIndex;
    int m_defaultsButtonIndex;

    bool m_returnPressed;
    bool m_enterPressed;
    bool m_escPressed;
};

#endif // SETTINGSDIALOG_H
