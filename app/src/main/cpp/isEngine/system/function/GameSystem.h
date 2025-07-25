/*
  is::Engine (Infinity Solutions Engine)
  Copyright (C) 2018-2025 Is Daouda <isdaouda.n@gmail.com>

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
*/

#ifndef GAMESYSTEM_H_INCLUDED
#define GAMESYSTEM_H_INCLUDED

#include "GameFunction.h"
#include "../graphic/GRM.h"
#include "../sound/GSM.h"

//////////////////////////////////////////////////////
// is::Engine version
//////////////////////////////////////////////////////
#define IS_ENGINE_VERSION_MAJOR 4
#define IS_ENGINE_VERSION_MINOR 0
#define IS_ENGINE_VERSION_PATCH 0

namespace is
{
class GameSystem;

/// Allows to play sound in container by his name if the option is activated
void GSMplaySound(const std::string& name, std::vector<std::shared_ptr<GameSound>>&GSMsound, GameSystem &gameSystem);

/// Allows to play music in container by his name if the option is activated
void GSMplayMusic(const std::string& name, std::vector<std::shared_ptr<
//#if !defined(__ANDROID__)
                  GameMusic
//#else
//                  GameSound
//#endif
                  >> &GSMmusic, GameSystem &gameSystem);

//////////////////////////////////////////////////////
/// \brief Class for manage game system
///
//////////////////////////////////////////////////////
class GameSystem : public GSM, public GRM
{
public:
    //////////////////////////////////////////////////////
    /// \brief Represent validation key on PC Platform
    ///
    /// It is used to know that button will be used for
    /// validation during a test
    //////////////////////////////////////////////////////
    enum ValidationButton
    {
        ALL_BUTTONS = 0, ///< Represent Mouse and Keyboard validation button (If it is used then it becomes touch action on android)
        KEYBOARD = -1,   ///< Represent Keyboard validation button
        MOUSE = -2       ///< Represent Mouse validation button (If it is used then it becomes touch action on android)
    };
    GameSystem(sf::RenderWindow &window);

    //////////////////////////////////////////////////////
    /// On PC Platform check if mouse / keyboard validation key button is pressed
    /// On Android check if user touch screen
    /// validation key is set in GameConfig.h
    ///
    /// \param finger Finger index (on Android)
    /// \param validationButton Represents the validation button to use to take the test
    //////////////////////////////////////////////////////
    virtual bool isPressed(int finger = 0) const;
    virtual bool isPressed(ValidationButton validationButton) const;

    //////////////////////////////////////////////////////
    /// \brief Check if key is pressed
    ///
    /// \return true if key is pressed false if not
    //////////////////////////////////////////////////////
    virtual bool keyIsPressed(sf::Keyboard::Key key) const;

    /*
     * When using is::Engine to develop on HTML 5 the keyboard and mouse keys are represented
     * by integers. They are no longer differentiated by an enum, so this function is no longer
     * useful when using the SDK which allows to develop on the web.
     */
    //////////////////////////////////////////////////////
    /// \brief Check if mouse button is pressed
    ///
    /// \return true if button is pressed false if not
    //////////////////////////////////////////////////////
    virtual bool keyIsPressed(sf::Mouse::Button button) const;

    //////////////////////////////////////////////////////
    /// \brief Check if file exist
    ///
    /// \return true is file is found false if not
    //////////////////////////////////////////////////////
    static bool fileExist(const std::string &fileName);

    /// Allows to remove file
    static void removeFile(const std::string &fileName);

    /// Allows to play a sound if the option is activated
    virtual void playSound(sf::Sound &obj);

    /// Allows to play a sound if the option is activated
    virtual void playSound(sf::Sound *obj);

    /// Allows to play sound in container by his name if the option is activated
    virtual void GSMplaySound(const std::string& name)
    {
        is::GSMplaySound(name, m_GSMsound, *this);
    }

    /// Allows to play a music if the option is activated
    virtual void playMusic(sf::Music &obj);

    /// Allows to play a music if the option is activated
    virtual void playMusic(sf::Music *obj);

    /// Allows to play music in container by his name if the option is activated
    virtual void GSMplayMusic(const std::string& name)
    {
        is::GSMplayMusic(name,
//#if !defined(__ANDROID__)
                         m_GSMmusic
//#else
//                         m_GSMsound
//#endif
                         , *this);
    }

    /// Allows to stop a sound
    virtual void stopSound(sf::Sound &obj);

    /// Allows to stop a music
    virtual void stopMusic(sf::Music &obj);

////////////////////////////////////////////////////////////
/// These methods below have the same role as those above.
/// The difference here is that their name starting with GSM
/// is replaced by GRM (Game Resource Manager).
////////////////////////////////////////////////////////////

    /// Allows to play sound in container by his name if the option is activated
    virtual void GRMplaySound(const std::string& name)
    {
        GSMplaySound(name);
    }

    /// Allows to play music in container by his name if the option is activated
    virtual void GRMplayMusic(const std::string& name)
    {
        GSMplayMusic(name);
    }

////////////////////////////////////////////////////////////
///
////////////////////////////////////////////////////////////

    /// Allows to use vibrate if the option is activated (only for Android)
    /// \param ms representing the duration of the vibrator in millisecond
    virtual void useVibrate(short ms);

    /// Save game configuration data
    virtual void saveConfig(const std::string &fileName);

    /// Load game configuration data
    virtual void loadConfig(const std::string &fileName);

    /// Save virtual game pad configuration data
    virtual void savePadConfig(const std::string &fileName);

    /// Load virtual game pad configuration data
    virtual void loadPadConfig(const std::string &fileName);

    ////////////////////////////////////////////////////////////
    // Do not touch these variables unless you know what you are doing
    bool  m_disableKey;    ///< If it is @a true all the engine functions that manage the inputs are deactivated (keyboard, mouse, touch)
    bool  m_enableSound;   ///< Used to find out if sound is enabled in option
    bool  m_enableMusic;   ///< Used to find out if music is enabled in option
    bool  m_enableVibrate; ///< Used to find out if vibrate is enabled in option
    bool  m_keyIsPressed;  ///< Used to find out if a key / button has been pressed
    bool  m_firstLaunch;   ///< Lets check if the game has been launched once
    bool  m_loadParentResources; ///< Allows to load parents resources once

    /// Represent the variable that stores the option validation key with the Mouse
    sf::Mouse::Button *m_validationMouseKey = nullptr;

    /// Represent the variable that stores the option validation key with the Keyboard
    sf::Keyboard::Key *m_validationKeyboardKey = nullptr;

    int m_gameLanguage; ///< Represents the index of the chosen language
    int m_padAlpha;     ///< Use to change the transparency of the Virtual Game Pad

    // These variable allows to position the Virtual Game Pad
    float m_padDirXPos, m_padDirYPos, m_padActionXPos, m_padActionYPos;
    float m_defaultPadDirXPos, m_defaultPadDirYPos, m_defaultPadActionXPos, m_defaultPadActionYPos;
    bool  m_permutePadAB;

    /// Application
    sf::RenderWindow &m_window;
    ////////////////////////////////////////////////////////////
};
}

#endif // GAMESYSTEM_H_INCLUDED
