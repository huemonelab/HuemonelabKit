#pragma once

#include <Arduino.h>
#include "../MD_MAX72xx/MD_MAX72xx.h"
/**
 * \file
 * \brief Main header file for the MD_Parola library
 */

// Granular selection of animations/functions to include in the library
// If an animation class is not used at all some memory savings can be made
// by excluding the animation code.
#ifndef ENA_MISC
#define ENA_MISC    1   ///< Enable miscellaneous animations
#endif
#ifndef ENA_WIPE
#define ENA_WIPE    1   ///< Enable wipe type animations
#endif
#ifndef ENA_SCAN
#define ENA_SCAN    1   ///< Enable scanning animations
#endif
#ifndef ENA_SCR_DIA
#define ENA_SCR_DIA 1   ///< Enable diagonal scrolling animation
#endif
#ifndef ENA_OPNCLS
#define ENA_OPNCLS  1   ///< Enable open and close scan effects
#endif
#ifndef ENA_GROW
#define ENA_GROW    1   ///< Enable grow effects
#endif
#ifndef ENA_SPRITE
#define ENA_SPRITE  1   ///< Enable sprite effects
#endif

// If function is not used at all, then some memory savings can be made
// by excluding associated code.
#ifndef ENA_GRAPHICS
#define ENA_GRAPHICS  1 ///< Enable graphics functionality
#endif

// Miscellaneous defines
#define ARRAY_SIZE(a) (sizeof(a) / sizeof((a)[0]))  ///< Generic macro for obtaining number of elements of an array
#define STATIC_ZONES 0    ///< Developer testing flag for quickly flipping between static/dynamic zones

#if STATIC_ZONES
#ifndef MAX_ZONES
#define MAX_ZONES 4     ///< Maximum number of zones allowed. Change to allow more or less zones but uses RAM even if not used.
#endif
#endif

// Zone column calculations
#define ZONE_START_COL(m) ((m) * COL_SIZE)    ///< The first column of the first zone module
#define ZONE_END_COL(m)   ((((m) + 1) * COL_SIZE) - 1)///< The last column of the last zone module

class MD_Parola;

/**
* Text alignment enumerated type specification.
*
* Used to define the display text alignment and to specify direction for
* scrolling and animations. In the situation where LEFT AND RIGHT are the only sensible
* options (eg, text scrolling direction), CENTER will behave the same as LEFT.
*/
enum textPosition_t
{
  PA_LEFT,    ///< The leftmost column for the first character will be on the left side of the display
  PA_CENTER,  ///< The text will be placed with equal number of blank display columns either side
  PA_RIGHT    ///< The rightmost column of the last character will be on the right side of the display
};

/**
* Text effects enumerated type specification.
*
* Used to define the effects to be used for the entry and exit of text in the display area.
*/
enum textEffect_t
{
  PA_NO_EFFECT,   ///< Used as a place filler, executes no operation
  PA_PRINT,       ///< Text just appears (printed)
  PA_SCROLL_UP,   ///< Text scrolls up through the display
  PA_SCROLL_DOWN, ///< Text scrolls down through the display
  PA_SCROLL_LEFT, ///< Text scrolls right to left on the display
  PA_SCROLL_RIGHT,///< Text scrolls left to right on the display
#if ENA_SPRITE
  PA_SPRITE,      ///< Text enters and exits using user defined sprite
#endif
#if ENA_MISC
  PA_SLICE,       ///< Text enters and exits a slice (column) at a time from the right
  PA_MESH,        ///< Text enters and exits in columns moving in alternate direction (U/D)
  PA_FADE,        ///< Text enters and exits by fading from/to 0 and intensity setting
  PA_DISSOLVE,    ///< Text dissolves from one display to another
  PA_BLINDS,      ///< Text is replaced behind vertical blinds
  PA_RANDOM,      ///< Text enters and exits as random dots
#endif //ENA_MISC
#if ENA_WIPE
  PA_WIPE,        ///< Text appears/disappears one column at a time, looks like it is wiped on and off
  PA_WIPE_CURSOR, ///< WIPE with a light bar ahead of the change
#endif  // ENA_WIPES
#if ENA_SCAN
  PA_SCAN_HORIZ,  ///< Scan the LED column one at a time then appears/disappear at end
  PA_SCAN_HORIZX, ///< Scan a blank column through the text one column at a time then appears/disappear at end
  PA_SCAN_VERT,   ///< Scan the LED row one at a time then appears/disappear at end
  PA_SCAN_VERTX,  ///< Scan a blank row through the text one row at a time then appears/disappear at end
#endif // ENA_SCAN
#if ENA_OPNCLS
  PA_OPENING,     ///< Appear and disappear from the center of the display, towards the ends
  PA_OPENING_CURSOR,  ///< OPENING with light bars ahead of the change
  PA_CLOSING,     ///< Appear and disappear from the ends of the display, towards the middle
  PA_CLOSING_CURSOR,  ///< CLOSING with light bars ahead of the change
#endif // ENA_OPNCLS
#if ENA_SCR_DIA
  PA_SCROLL_UP_LEFT,  ///< Text moves in/out in a diagonal path up and left (North East)
  PA_SCROLL_UP_RIGHT, ///< Text moves in/out in a diagonal path up and right (North West)
  PA_SCROLL_DOWN_LEFT,  ///< Text moves in/out in a diagonal path down and left (South East)
  PA_SCROLL_DOWN_RIGHT, ///< Text moves in/out in a diagonal path down and right (North West)
#endif // ENA_SCR_DIA
#if ENA_GROW
  PA_GROW_UP,     ///< Text grows from the bottom up and shrinks from the top down
  PA_GROW_DOWN,   ///< Text grows from the top down and and shrinks from the bottom up
#endif // ENA_GROW
};

/**
 * Zone effect enumerated type specification.
 *
 * Used to define the effects to be used for text in the zone.
 *
 * The FLIP_UD and FLIP_LR effects are specifically designed to allow rectangular shaped display
 * modules (like Parola or Generic types) to be placed in an inverted position to allow all matrices
 * to be tightly packed into a 2 line display. One of the lines must be flipped horizontally and
 * vertically to remain legible in this configuration.
 */
enum zoneEffect_t
{
  PA_FLIP_UD, ///< Flip the zone Up to Down (effectively upside down). Works with all textEffect_t values
  PA_FLIP_LR, ///< Flip the zone Left to Right (effectively mirrored). Does not work with textEffect_t types SLICE, SCROLL_LEFT, SCROLL_RIGHT
};

/**
 * Zone object for the Parola library.
 * This class contains the text to be displayed and all the attributes for the zone.
 */
class MD_PZone
{
public:
  /**
   * Class constructor.
   *
   * Instantiate a new instance of the class.
   */
  MD_PZone(void);

  /**
   * Initialize the object.
   *
   * Initialize the object data. This will be called to initialize
   * new data for the class that cannot be done during the object creation.
   *
   * \param p pointer to the parent's MD_MAX72xx object.
   */
  void begin(MD_MAX72XX *p);

  /**
   * Class Destructor.
   *
   * Release allocated memory and does the necessary to clean up once the object is
   * no longer required.
   */
  ~MD_PZone(void);

  //--------------------------------------------------------------
  /** \name Methods for core object control.
   * @{
   */
  /**
   * Animate the zone.
   *
   * Animate using the currently specified text and animation parameters.
   * This method is invoked from the main Parola object.
   *
   * \return bool true if the zone animation has completed, false otherwise.
   */
  bool zoneAnimate(void);

  /**
   * Get the completion status.
   *
   * Return the current completion status for the zone animation.
   *
   * See comments for the MD_Parola getZoneStatus() method.
   *
   * \return bool true if the zone animation is completed
   */
  bool getStatus(void) { return (_fsmState == END); }

  /**
   * Get the start and end parameters for a zone.
   *
   * See comments for the MD_Parola namesake method.
   *
   * \param zStart  value for the start module number placed here [0..numZones-1].
   * \param zEnd  value for the end module number placed here [0..numZones-1].
   */
  inline void getZone(uint8_t &zStart, uint8_t &zEnd) { zStart = _zoneStart; zEnd = _zoneEnd; }

  /**
  * Check if animation frame has advanced.
  *
  * Check if the last call to zoneAnimate() resulted in the animation frame advancing by
  * one or more frames in one or more zones.
  *
  * \return True if the animation frame advanced in any of the display zones.
  */
  bool isAnimationAdvanced(void) { return(_animationAdvanced); }

  /**
   * Clear the zone.
   *
   * See comments for the MD_Parola namesake method.
   *
   */
  void zoneClear(void) { _MX->clear(_zoneStart, _zoneEnd); if (_inverted) _MX->transform(_zoneStart, _zoneEnd, MD_MAX72XX::TINV); }

  /**
   * Reset the current zone animation to restart.
   *
   * See comments for the MD_Parola namesake method.
   *
   */
  inline void zoneReset(void) { _fsmState = INITIALISE; }

  /**
  * Shutdown or resume zone hardware.
  *
  * See comments for the MD_Parola namesake method.
  *
  * \param b  boolean value to shutdown (true) or resume (false).
  */
  void zoneShutdown(bool b) { _MX->control(_zoneStart, _zoneEnd, MD_MAX72XX::SHUTDOWN, b ? MD_MAX72XX::ON : MD_MAX72XX::OFF); }

  /**
   * Suspend or resume zone updates.
   *
   * See comments for the MD_Parola namesake method.
   *
   * \param b boolean value to suspend (true) or resume (false).
   */
  inline void zoneSuspend(bool b) { _suspend = b; }

  /**
   * Set the start and end parameters for a zone.
   *
   * See comments for the MD_Parola namesake method.
   *
   * \param zStart  the first module number for the zone [0..numZones-1].
   * \param zEnd  the last module number for the zone [0..numZones-1].
   */
  inline void setZone(uint8_t zStart, uint8_t zEnd) { _zoneStart = zStart; _zoneEnd = zEnd; }

  /** @} */
  //--------------------------------------------------------------
  /** \name Support methods for visually adjusting the display.
   * @{
   */

  /**
   * Get the zone inter-character spacing in columns.
   *
   * \return the current setting for the space between characters in columns.
   */
  inline uint8_t getCharSpacing(void) { return _charSpacing; }

  /**
  * Get the zone brightness.
  *
  * Get the intensity (brightness) of the display.
  *
  * \return The intensity setting.
  */
  inline uint8_t getIntensity() { return _intensity; }

  /**
   * Get the zone current invert state.
   *
   * See the setInvert() method.
   *
   * \return the inverted boolean value.
   */
  inline bool getInvert(void) { return _inverted; }

  /**
   * Get the zone pause time.
   *
   * See the setPause() method.
   *
   * \return the pause value in milliseconds.
   */
  inline uint16_t getPause(void) { return _pauseTime; }

  /**
     * Get the horizontal Scroll spacing.
     *
     * See the setScrollSpacing() method
     *
     * \return the space between message in columns.
     */
  inline uint16_t getScrollSpacing(void) { return _scrollDistance; }

  /**
   * Get the zone animation speed.
   *
   * See the setSpeed() method.
   * This should be replaced with either getSpeedIn() or getSpeedOut()
   * unless it is known that both directions are running at the same speed.
   *
   * \return the IN speed value.
   */
  inline uint16_t getSpeed(void) { return getSpeedIn(); }

  /**
   * Get the zone animation IN speed.
   *
   * See the setSpeed() method.
   *
   * \return the speed value.
   */
  inline uint16_t getSpeedIn(void) { return _tickTimeIn; }

  /**
   * Get the zone animation OUT speed.
   *
   * See the setSpeed() method.
   *
   * \return the speed value.
   */
  inline uint16_t getSpeedOut(void) { return _tickTimeOut; }
  
  /**
  * Get the zone animation start time.
  *
  * See the setSynchTime() method
  *
  * \return the internal time reference.
  */
  inline uint32_t getSynchTime(void) { return _lastRunTime; }

  /**
   * Get the current text alignment specification.
   *
   * \return the current text alignment setting
   */
  inline textPosition_t getTextAlignment(void) { return _textAlignment; }

  /**
   *  Get the width of text in columns
   *
   * Calculate the width of the characters and the space between them
   * using the current font and text settings.
   *
   * \param p   pointer to a text string
   * \return the width of the string in display columns
   */
   uint16_t getTextWidth(const uint8_t* p);

  /**
   * Get the value of specified display effect.
   *
   * The display effect is one of the zoneEffect_t types. The returned value will be
   * true if the attribute is set, false if the attribute is not set.
   *
   * \param ze  the required text alignment.
   * \return true if the value is set, false otherwise.
   */
  boolean getZoneEffect(zoneEffect_t ze);

  /**
   * Set the zone inter-character spacing in columns.
   *
   * Set the number of blank columns between characters when they are displayed.
   *
   * \param cs  space between characters in columns.
   */
  inline void setCharSpacing(uint8_t cs) { _charSpacing = cs; allocateFontBuffer(); }

  /**
   * Set the zone brightness.
   *
   * Set the intensity (brightness) of the display.
   *
   * \param intensity the intensity to set the display (0-15).
   */
  inline void setIntensity(uint8_t intensity) { _intensity = intensity; _MX->control(_zoneStart, _zoneEnd, MD_MAX72XX::INTENSITY, _intensity); }

  /**
   * Invert the zone display.
   *
   * Set the display to inverted (ON LED turns OFF and vice versa).
   *
   * \param invert  true for inverted display, false for normal display
   */
  inline void setInvert(uint8_t invert) { _inverted = invert; }

  /**
   * Set the pause between ENTER and EXIT animations for this zone.
   *
   * Between each entry and exit, the library will pause by the number of milliseconds
   * specified to allow the viewer to read the message. For continuous scrolling displays
   * this should be set to the same value as the display speed.
   *
   * \param pause the time, in milliseconds, between animations.
   */
  inline void setPause(uint16_t pause) { _pauseTime = pause; }

  /**
   * Set the horizontal scrolling distance between messages.
   *
   * When scrolling horizontally, the distance between the end of one message and the
   * start of the next can be set using this method. Normal operation is for the message
   * to be fully off the display before the new message starts.
   * Set to zero for default behavior.
   *
   * \param space the spacing, in columns, between messages; zero for default behaviour..
   */
  inline void setScrollSpacing(uint16_t space) { _scrollDistance = space; }

  /**
   * Set the zone animation frame speed.
   *
   * The speed of the display is the 'tick' time between animation frames. The lower this time
   * the faster the animation; set it to zero to run as fast as possible.
   *
   * This method will set the same value for both IN and OUT animations speed.
   *
   * \param speed the time, in milliseconds, between animation frames.
   */
  inline void setSpeed(uint16_t speed) { setSpeedInOut(speed, speed); }

  /**
   * Set separate IN and OUT zone animation frame speed.
   *
   * The speed of the display is the 'tick' time between animation frames. The lower this time
   * the faster the animation; set it to zero to run as fast as possible.
   *
   * This method will set both the IN and OUT animations separately to the specified speed.
   *
   * \param speedIn the time, in milliseconds, between IN animation frames.
   * \param speedOut the time, in milliseconds, between OUT animation frames.
   */
  inline void setSpeedInOut(uint16_t speedIn, uint16_t speedOut) { _tickTimeIn = speedIn; _tickTimeOut = speedOut; }

#if ENA_SPRITE
  /**
  * Set data for user sprite effects.
  *
  * Set up the data parameters for user sprite text entry/exit effects.
  * See the comments for the namesake method in MD_Parola.
  *
  * \param inData pointer to the data table defining the entry sprite.
  * \param inWidth the width (in bytes) of each frame of the sprite.
  * \param inFrames the number of frames for the sprite.
  * \param outData pointer to the data table that is inWidth*InFrames in size.
  * \param outWidth the width (in bytes) of each frame of the sprite.
  * \param outFrames the number of frames for the sprite.
  */
  void setSpriteData(const uint8_t *inData,  uint8_t inWidth,  uint8_t inFrames,
                     const uint8_t *outData, uint8_t outWidth, uint8_t outFrames);
#endif

  /**
  * Set the zone animation start time.
  *
  * Each zone animation has an associated start time. The start time
  * defaults to the time when the zone is initialized. This method allows
  * synchronization between zones by setting the same start time. Should be
  * used in conjunction with the getSynchTime() method as the return value
  * should only be treated as an internal reference and arbitrary values
  * will result in irregular behavior.
  *
  * \param zt the required start time.
  */
  inline void setSynchTime(uint32_t zt) { _lastRunTime = zt; }

  /**
   * Set the text alignment within the zone.
   *
   * Text alignment is specified as one of the values in textPosition_t.
   *
   * \param ta  the required text alignment.
   */
  inline void setTextAlignment(textPosition_t ta) { _textAlignment = ta; }

  /**
   * Set the pointer to the text buffer for this zone.
   *
   * Sets the text buffer to be a pointer to user data.
   * See the comments for the namesake method in MD_Parola.
   *
   * \param pb  pointer to the text buffer to be used.
   */
  inline void setTextBuffer(const char *pb) { _pText = (const uint8_t *)pb; }

  /**
   * Set the entry and exit text effects for the zone.
   *
   * See the comments for the namesake method in MD_Parola.
   *
   * \param effectIn  the entry effect, one of the textEffect_t enumerated values.
   * \param effectOut the exit effect, one of the textEffect_t enumerated values.
   */
  inline void setTextEffect(textEffect_t effectIn, textEffect_t effectOut) { _effectIn = (effectIn == PA_NO_EFFECT ? PA_PRINT : effectIn), _effectOut = effectOut; }

  /**
   * Set the zone display effect.
   *
   * The display effect is one of the zoneEffect_t types, and this will be set (true) or
   * reset (false) depending on the boolean value. The resulting zone display will be
   * modified as per the required effect.
   *
   * \param b set the value if true, reset the value if false
   * \param ze  the required text alignment.
   */
  void setZoneEffect(boolean b, zoneEffect_t ze);

  /** @} */

  //--------------------------------------------------------------
  /** \name Support methods for fonts and characters.
   * @{
   */

  /**
   * Add a user defined character to the replacement list.
   *
   * Add a replacement characters to the user defined list. The character data must be
   * the same as for a single character in the font definition file. If a character is
   * specified with a code the same as an existing character the existing data will be
   * substituted for the new data. A character code of 0 is illegal as this denotes the
   * end of string character for C++ and cannot be used in an actual string.
   * The library does not copy the in the data in the data definition but only retains
   * a pointer to the data, so any changes to the data storage in the calling program will
   * be reflected in the library.
   *
   * \param code  code for the character data.
   * \param data  pointer to the character data.
   * \return true of the character was inserted in the substitution list.
   */
  bool addChar(uint16_t code, const uint8_t *data);

  /**
   * Delete a user defined character to the replacement list.
   *
   * Delete a replacement character to the user defined list. A character code of 0 is
   * illegal as this denotes the end of string character for C++ and cannot be used in
   * an actual string.
   *
   * \param code  ASCII code for the character data.
   * \return true of the character was found in the substitution list.
   */
  bool delChar(uint16_t code);

  /**
   * Get the display font.
   *
   * Return the current font table pointer for this zone.
   *
   * \return Pointer to the font definition used.
   */
  inline MD_MAX72XX::fontType_t* getZoneFont(void) { return _fontDef; };

  /**
   * Set the display font.
   *
   * See comments for the namesake Parola method.
   *
   * \param fontDef Pointer to the font definition to be used.
   */
  void setZoneFont(MD_MAX72XX::fontType_t *fontDef) { _fontDef = fontDef; _MX->setFont(_fontDef); allocateFontBuffer(); }

  /** @} */

#if ENA_GRAPHICS
  //--------------------------------------------------------------
  /** \name Support methods for graphics.
  * @{
  */
  /**
  * Get the start and end column numbers for the zone.
  *
  * Returns the start and end column numbers for the zone display.
  * This retains consistency between user code and library.
  *
  * \param startColumn the by-reference parameter that will hold the return value for the start column.
  * \param endColumn the by-reference parameter that will hold the return value for the end column.
  */
  void getZoneExtent(uint16_t &startColumn, uint16_t &endColumn) { startColumn = ZONE_START_COL(_zoneStart); endColumn = ZONE_END_COL(_zoneEnd); }

  /**
  * Get the start and end column numbers for the text displayed.
  *
  * Returns the start and end column numbers for the text displayed in the zone.
  * This retains consistency between user code and library.
  *
  * \param startColumn the by-reference parameter that will hold the return value for the start column.
  * \param endColumn the by-reference parameter that will hold the return value for the end column.
  */
  void getTextExtent(uint16_t &startColumn, uint16_t &endColumn) { startColumn = _limitLeft; endColumn = _limitRight; }

  /** @} */
#endif

private:
   /***
    *  Finite State machine states enumerated type.
  */
  enum fsmState_t
  {
    INITIALISE,     ///< Initialize all variables
    GET_FIRST_CHAR, ///< Get the first character
    GET_NEXT_CHAR,  ///< Get the next character
    PUT_CHAR,       ///< Placing a character
    PUT_FILLER,     ///< Placing filler (blank) columns
    PAUSE,          ///< Pausing between animations
    END             ///< Display cycle has completed
  };

  /***
    *  Structure for list of user defined characters substitutions.
  */
  struct charDef_t
  {
    uint16_t      code;   ///< the ASCII code for the user defined character
    const uint8_t *data;  ///< user supplied data
    charDef_t     *next;  ///< next in the list
  };

  MD_MAX72XX  *_MX;   ///< Pointer to parent's MD_MAX72xx object passed in at begin()

  // Time and speed controlling data and methods
  bool      _suspend;     // don't do anything
  uint32_t  _lastRunTime; // the millis() value for when the animation was last run
  uint16_t  _tickTimeIn;  // the time between IN animations in milliseconds
  uint16_t  _tickTimeOut; // the time between OUT animations in milliseconds
  uint16_t  _pauseTime;   // time to pause the animation between 'in' and 'out'

  // Display control data and methods
  fsmState_t      _fsmState;          // fsm state for all FSMs used to display text
  uint16_t        _textLen;           // length of current text in columns
  int16_t         _limitLeft;         // leftmost limit for the current display effect
  int16_t         _limitRight;        // rightmost limit for the current display effect
  bool            _limitOverflow;     // true if the text will overflow the display
  textPosition_t  _textAlignment;     // current text alignment
  textEffect_t    _effectIn;          // the effect for text entering the display
  textEffect_t    _effectOut;         // the effect for text exiting the display
  bool            _moveIn;            // animation is moving IN when true, OUT when false
  bool            _inverted;          // true if the display needs to be inverted
  uint16_t        _scrollDistance;    // the space in columns between the end of one message and the start of the next
  uint8_t         _zoneEffect;        // bit mapped zone effects
  uint8_t         _intensity;         // display intensity
  bool            _animationAdvanced; // true is animation advanced inthe last animation call

  void      setInitialConditions(void);       // set up initial conditions for an effect
  bool      calcTextLimits(const uint8_t *p); // calculate the right and left limits for the text

  // Variables used in the effects routines. These can be used by the functions as needed.
  uint8_t   _zoneStart;   // First zone module number
  uint8_t   _zoneEnd;     // Last zone module number
  int16_t   _nextPos;     // Next position for animation. Can be used in several different ways depending on the function.
  int8_t    _posOffset;   // Looping increment depends on the direction of the scan for animation
  int16_t   _startPos;    // Start position for the text LED
  int16_t   _endPos;      // End limit for the text LED.

  void setInitialEffectConditions(void); // set the initial conditions for loops in the FSM

  // Character buffer handling data and methods
  const uint8_t *_pText;             // pointer to text buffer from user call
  const uint8_t *_pCurChar;          // the current character being processed in the text
  bool       _endOfText;             // true when the end of the text string has been reached.
  void       moveTextPointer(void);  // move the text pointer depending on direction of buffer scan

  bool getFirstChar(uint8_t &len);   // put the first Text char into the char buffer
  bool getNextChar(uint8_t &len);    // put the next Text char into the char buffer

  // Font character handling data and methods
  charDef_t *_userChars;  // the root of the list of user defined characters
  uint8_t   _cBufSize;    // allocated size of the array for loading character font (cBuf)
  uint8_t   *_cBuf;       // buffer for loading character font - allocated when font is set
  uint8_t   _charSpacing; // spacing in columns between characters
  uint8_t   _charCols;    // number of columns for this character
  int16_t   _countCols;   // count of number of columns already shown
  MD_MAX72XX::fontType_t  *_fontDef;  // font for this zone

  void      allocateFontBuffer(void); // allocate _cBuf based on the size of the largest font characters
  uint8_t   findChar(uint16_t code, uint8_t size, uint8_t *cBuf); // look for user defined character
  uint8_t   makeChar(uint16_t c, bool addBlank);  // load a character bitmap and add in trailing _charSpacing blanks if req'd
  void      reverseBuf(uint8_t *p, uint8_t size); // reverse the elements of the buffer
  void      invertBuf(uint8_t *p, uint8_t size);  // invert the elements of the buffer

  /// Sprite management
#if ENA_SPRITE
  uint8_t *_spriteInData, *_spriteOutData;
  uint8_t _spriteInWidth, _spriteOutWidth;
  uint8_t _spriteInFrames, _spriteOutFrames;
#endif

  // Debugging aid
  const char *state2string(fsmState_t s);

  // Effect functions
  void  commonPrint(void);
  void  effectPrint(bool bIn);
  void  effectVScroll(bool bUp, bool bIn);
  void  effectHScroll(bool bLeft, bool bIn);
#if ENA_MISC
  void  effectSlice(bool bIn);
  void  effectMesh(bool bIn);
  void  effectFade(bool bIn);
  void  effectBlinds(bool bIn);
  void  effectDissolve(bool bIn);
  void  effectRandom(bool bIn);
#endif // ENA_MISC
#if ENA_SPRITE
  void  effectSprite(bool bIn, uint8_t id);
#endif // ENA_SPRITE
#if ENA_WIPE
  void  effectWipe(bool bLightBar, bool bIn);
#endif // ENA_WIPE
#if ENA_OPNCLS
  void  effectOpen(bool bLightBar, bool bIn);
  void  effectClose(bool bLightBar, bool bIn);
#endif // ENA_OPNCLS
#if ENA_SCR_DIA
  void  effectDiag(bool bUp, bool bLeft, bool bIn);
#endif // ENA_SCR_DIA
#if ENA_SCAN
  void  effectHScan(bool bIn, bool bBlank);
  void  effectVScan(bool bIn, bool bBlank);
#endif // ENA_SCAN
#if ENA_GROW
  void  effectGrow(bool bUp, bool bIn);
#endif // ENA_GROW
};

/**
 * Core object for the Parola library.
 * This class contains one or more zones for display.
 */
class MD_Parola : public Print
{
public:
  /**
   * Class constructor - arbitrary output pins.
   *
   * Instantiate a new instance of the class. The parameters passed are used to
   * connect the software to the hardware using the MD_MAX72XX class.
   *
   * See documentation for the MD_MAX72XX library for detailed explanation of parameters.
   *
   * \param mod       the hardware module type used in the application. One of the MD_MAX72XX::moduleType_t values.
   * \param dataPin   output on the Arduino where data gets shifted out.
   * \param clkPin    output for the clock signal.
   * \param csPin     output for selecting the device.
   * \param numDevices  number of devices connected. Default is 1 if not supplied.
   */
  //* Class definition
  MD_Parola(MD_MAX72XX::moduleType_t mod, uint8_t dataPin, uint8_t clkPin, uint8_t csPin, uint8_t numDevices = 1):
    _D(mod, dataPin, clkPin, csPin, numDevices), _numModules(numDevices)
  {}

  /**
   * Class constructor - default SPI hardware interface.
   *
   * Instantiate a new instance of the class. The parameters passed are used to
   * connect the software to the hardware using the MD_MAX72XX class.
   *
   * See documentation for the MD_MAX72XX library for detailed explanation of parameters.
   *
   * \param mod       the hardware module type used in the application. One of the MD_MAX72XX::moduleType_t values.
   * \param csPin     output for selecting the device.
   * \param numDevices  number of devices connected. Default is 1 if not supplied.
   */
  MD_Parola(MD_MAX72XX::moduleType_t mod, uint8_t csPin, uint8_t numDevices = 1):
    _D(mod, csPin, numDevices), _numModules(numDevices)
  {}

    /**
   * Class Constructor - specify SPI hardware interface.
   *
   * Instantiate a new instance of the class with a specified SPI object. This
   * allows a specific SPI interface to be specified for architectures with more 
   * than one hardware SPI interface. 
   *
   * See documentation for the MD_MAX72XX library for detailed explanation of parameters.
   *
   * \param mod     module type used in this application. One of the moduleType_t values.
   * \param spi     reference to the SPI object to use for comms to the device
   * \param csPin   output for selecting the device.
   * \param numDevices  number of devices connected. Default is 1 if not supplied.
   */
  MD_Parola(MD_MAX72XX::moduleType_t mod, SPIClass &spi, uint8_t csPin, uint8_t numDevices = 1):
    _D(mod, spi, csPin, numDevices), _numModules(numDevices)
  {}

  /**
   * Initialize the object.
   *
   * Initialize the object data. This needs to be called during setup() to initialize new
   * data for the class that cannot be done during the object creation. This form of the
   * method is for backward compatibility and creates one zone for the entire display.
   */
  void begin(void) { begin(1); };

  /**
   * Initialize the object.
   *
   * Initialize the object data. This needs to be called during setup() to initialize new
   * data for the class that cannot be done during the object creation. This form of the
   * method allows specifying the number of zones used. The module limits for the individual
   * zones are initialized separately using setZone(), which should be done immediately after
   * the invoking begin().
   *
   * \sa setZone()
   *
   * \param numZones  maximum number of zones
   */
  void begin(uint8_t numZones);

  /**
   * Class Destructor.
   *
   * Release allocated memory and does the necessary to clean up once the object is
   * no longer required.
   */
  ~MD_Parola(void);

  //--------------------------------------------------------------
  /** \name Methods for core object control.
   * @{
   */
  /**
   * Animate the display.
   *
   * Animate all the zones in the display using the currently specified text and
   * animation parameters. This method needs to be invoked as often as possible
   * to ensure smooth animation. The animation is governed by a time tick that
   * is set by the setSpeed() or setSpeedInOut() methods and it will pause between 
   * entry and exit using the time set by the setPause() method.
   *
   * The calling program should monitor the return value for 'true' in order to either
   * reset the zone animation or supply another string for display. A 'true' return
   * value means that one or more zones have completed their animation.
   *
   * Not all calls to this method result in an animation, as this is governed by
   * the timing parameters set for the animation. To determine when an animation has
   * advanced during the call, the user code can call the isAnimationAdvanced() method.
   *
   * \return bool true if at least one zone animation has completed, false otherwise.
   */
  bool displayAnimate(void);

  /**
   * Get the completion status for a zone.
   *
   * This method is to determine which zone has completed when displayAnimate()
   * has returned a completion status.
   *
   * The calling program should monitor the return value for 'true' in order to either
   * reset the zone animation or supply another string for display. A 'true' return
   * value means that the zone has completed its animation cycle.
   *
   * \param z     specified zone
   * \return bool true if the zone animation has completed, false otherwise.
   */
  bool getZoneStatus(uint8_t z) { if (z < _numZones) return(_Z[z].getStatus()); else return(true); }

  /**
   * Clear the display.
   *
   * Clear all the zones in the current display.
   */
  void displayClear(void) { for (uint8_t i = 0; i < _numZones; i++) _Z[i].zoneClear(); }

  /**
   * Clear one zone in the display.
   *
   * Clear the specified zone in the current display.
   *
   * \param z   specified zone
   */
  void displayClear(uint8_t z) { if (z < _numZones) _Z[z].zoneClear(); }

  /**
   * Reset the current animation to restart for all zones.
   *
   * This method is used to reset all the zone animations an animation back to the start
   * of their cycle current cycle.
   * It is normally invoked after all the parameters for a display are set and the
   * animation needs to be started (or restarted).
   */
  void displayReset(void) { for (uint8_t i = 0; i < _numZones; i++) _Z[i].zoneReset(); }

  /**
   * Reset the current animation to restart for the specified zone.
   *
   * See the comments for the 'all zones' variant of this method.
   *
   * \param z specified zone
   */
  void displayReset(uint8_t z) { if (z < _numZones) _Z[z].zoneReset(); }

  /**
  * Shutdown or restart display hardware.
  *
  * Shutdown the display hardware to a low power state. The display will
  * be blank during the shutdown. Calling animate() will continue to
  * animate the display in the memory buffers but this will not be visible
  * on the display (ie, the libraries still function but the display does not).
  *
  * \param b  boolean value to shutdown (true) or resume (false).
  */
  void displayShutdown(bool b) { for (uint8_t i = 0; i < _numZones; i++) _Z[i].zoneShutdown(b); }

  /**
  * Suspend or resume display updates.
  *
  * Stop the current display animation. When pausing it leaves the
  * display showing the current text. Resuming will restart the animation where
  * it left off. To reset the animation back to the beginning, use the
  * displayReset() method.
  *
  * \param b  boolean value to suspend (true) or resume (false).
  */
  void displaySuspend(bool b) { for (uint8_t i = 0; i < _numZones; i++) _Z[i].zoneSuspend(b); }

  /**
  * Check if animation frame has advanced.
  *
  * Check if the last call to animate() resulted in the animation frame advancing by
  * one or more frames in one or more zones. Useful to integrate graphics into the
  * display as they may be affected by the text animation.
  *
  * For displays with more than one zone, the user code will need to interrogate each zone
  * to determine whether the animation advanced in that zone.
  *
  * \return True if the animation frame advanced in any of the display zones.
  */
  bool isAnimationAdvanced(void) { bool b = false; for (uint8_t i = 0; i < _numZones; i++) b |= _Z[i].isAnimationAdvanced(); return(b); }

  /**
   * Get the module limits for a zone.
   *
   * Once a zone has been defined, this method will return the 
   * start and end module that were defined for the specified zone.
   *
   * \sa setZone()
   *
   * \param z   zone number.
   * \param moduleStart returns the first module number for the zone [0..numZones-1].
   * \param moduleEnd   returns last module number for the zone [0..numZones-1].
   */
  inline void getZone(uint8_t z, uint8_t &moduleStart, uint8_t &moduleEnd) { if (z < _numZones) _Z[z].getZone(moduleStart, moduleEnd); }

  /**
   * Define the module limits for a zone.
   *
   * When multiple zones are defined, the library needs to know the contiguous module
   * ranges that make up the different zones. If the library has been started with only
   * one zone then it will automatically initialize the zone to be the entire range for
   * the display modules, so calling this function is not required. However, when multiple
   * zones are defined, setZone() for each zone should be should be invoked immediately 
   * after the call to begin().
   *
   * A module is a unit of 8x8 LEDs, as defined in the MD_MAX72xx library.
   * Zones should not overlap or unexpected results will occur.
   *
   * \sa begin()
   *
   * \param z   zone number.
   * \param moduleStart the first module number for the zone [0..numZones-1].
   * \param moduleEnd   the last module number for the zone [0..numZones-1].
   * \return true if set, false otherwise.
   */
  bool setZone(uint8_t z, uint8_t moduleStart, uint8_t moduleEnd);

  /** @} */
  //--------------------------------------------------------------
  /** \name Methods for quick start displays.
   * @{
   */
  /**
   * Easy start for a scrolling text display.
   *
   * This method is a convenient way to set up a scrolling display. All the data
   * necessary for setup is passed through as parameters and the display animation
   * is started. Assumes one zone only (zone 0).
   *
   * \param pText   parameter suitable for the setTextBuffer() method.
   * \param align   parameter suitable for the the setTextAlignment() method.
   * \param effect  parameter suitable for the the setTextEffect() method.
   * \param speed   parameter suitable for the setSpeed() method.
   */
  inline void displayScroll(const char *pText, textPosition_t align, textEffect_t effect, uint16_t speed)
  {
    displayZoneText(0, pText, align, speed, 0, effect, effect);
  }

 /**
   * Easy start for a non-scrolling text display.
   *
   * This method is a convenient way to set up a static text display. All the data
   * necessary for setup is passed through as parameters and the display animation
   * is started. Assumes one zone only (zone 0).
   *
   * \param pText parameter suitable for the setTextBuffer() method.
   * \param align parameter suitable for the the setTextAlignment() method.
   * \param speed parameter suitable for the setSpeed() method.
   * \param pause parameter suitable for the setPause() method.
   * \param effectIn  parameter suitable for the setTextEffect() method.
   * \param effectOut parameter suitable for the setTextEffect() method.
   */
  inline void displayText(const char *pText, textPosition_t align, uint16_t speed, uint16_t pause, textEffect_t effectIn, textEffect_t effectOut = PA_NO_EFFECT)
    { displayZoneText(0, pText, align, speed, pause, effectIn, effectOut); }

 /**
   * Easy start for a non-scrolling zone text display.
   *
   * This method is a convenient way to set up a static text display within the
   * specified zone. All the data necessary for setup is passed through as
   * parameters and the display animation is started.
   *
   * \param z   zone specified.
   * \param pText parameter suitable for the setTextBuffer() method.
   * \param align parameter suitable for the the setTextAlignment() method.
   * \param speed parameter suitable for the setSpeed() method.
   * \param pause parameter suitable for the setPause() method.
   * \param effectIn  parameter suitable for the setTextEffect() method.
   * \param effectOut parameter suitable for the setTextEffect() method.
   */
  void displayZoneText(uint8_t z, const char *pText, textPosition_t align, uint16_t speed, uint16_t pause, textEffect_t effectIn, textEffect_t effectOut = PA_NO_EFFECT);

  /** @} */
  //--------------------------------------------------------------
  /** \name Support methods for visually adjusting the display.
   * @{
   */

  /**
   * Get the inter-character spacing in columns.
   *
   * \return the current setting for the space between characters in columns. Assumes one zone only.
   */
  inline uint8_t getCharSpacing(void) { return getCharSpacing(0); }

  /**
   * Get the inter-character spacing in columns for a specific zone.
   *
   * \param z   zone number.
   * \return the current setting for the space between characters in columns.
   */
  inline uint8_t getCharSpacing(uint8_t z) { return (z < _numZones ? _Z[z].getCharSpacing() : 0); }

  /**
   * Get the current display invert state.
   *
   * See the setInvert() method.
   *
   * \return true if the display is inverted. Assumes one zone only.
   */
  inline bool getInvert(void) { return getInvert(0); }

  /**
   * Get the current display invert state for a specific zone.
   *
   * See the setInvert() method.
   *
   * \param z   zone number.
   * \return the inverted boolean value for the specified zone.
   */
  inline bool getInvert(uint8_t z) { return (z < _numZones ? _Z[z].getInvert() : false); }

  /**
   * Get the current pause time.
   *
   * See the setPause() method. Assumes one zone only.
   *
   * \return the pause value in milliseconds.
   */
  inline uint16_t getPause(void) { return getPause(0); }

  /**
   * Get the current pause time for a specific zone.
   *
   * See the setPause() method.
   *
   * \param z   zone number.
   * \return the pause value in milliseconds for the specified zone.
   */
  inline uint16_t getPause(uint8_t z) { return (z < _numZones ? _Z[z].getPause() : 0); }

  /**
   * Get the horizontal scrolling spacing.
   *
   * See the setScrollSpacing() method. Assumes one zone only
   *
   * \return the speed value.
   */
  inline uint16_t getScrollSpacing(void) { return _Z[0].getScrollSpacing(); }

  /**
   * Get the current IN animation speed.
   *
   * See the setSpeed() method. Assumes one zone only
   *
   * \return the speed value.
   */
  inline uint16_t getSpeed(void) { return getSpeed(0); }

  /**
   * Get the current IN animation speed for the specified zone.
   *
   * See the setSpeed() method.
   *
   * \param z   zone number.
   * \return the speed value for the specified zone.
   */
  inline uint16_t getSpeed(uint8_t z) { return (z < _numZones ? _Z[z].getSpeed() : 0); }

  /**
   * Get the current IN animation speed for the specified zone.
   *
   * See the setSpeed() method.
   *
   * \param z   zone number.
   * \return the IN speed value for the specified zone.
   */
  inline uint16_t getSpeedIn(uint8_t z) { return (z < _numZones ? _Z[z].getSpeedIn() : 0); }

  /**
   * Get the current OUT animation speed for the specified zone.
   *
   * See the setSpeed() method.
   *
   * \param z   zone number.
   * \return the OUT speed value for the specified zone.
   */
  inline uint16_t getSpeedOut(uint8_t z) { return (z < _numZones ? _Z[z].getSpeedOut() : 0); }

 /**
   * Get the current text alignment specification.
   *
   * Assumes one zone only.
   *
   * \return the current text alignment setting.
   */
  inline textPosition_t getTextAlignment(void) { return getTextAlignment(0); }

 /**
   * Get the current text alignment specification for the specified zone.
   *
   * \param z   zone number.
   * \return the current text alignment setting for the specified zone.
   */
  inline textPosition_t getTextAlignment(uint8_t z) { return (z < _numZones ? _Z[z].getTextAlignment() : PA_CENTER); }

 /**
   * Get the text width in columns

   * Evaluate the width in column for the text string *p as the sum of all 
   * the characters and the space between them, using the currently assigned font.
   * Assumes one zone display.
   *
   * \param p   nul terminate character string to evaluate.
   * \return the number of columns used to display the text.
   */
  inline uint16_t getTextColumns(const char *p) { return(getTextColumns(0, p)); }
  
 /**
   * Get the text width in columns

   * Evaluate the width in column for the text string *p in the zone specified, as 
   * the sum of all the characters and the space between them. As each zone can  
   * display using a different font table, the result can vary between zones.
   *
   * \param z   zone number.
   * \param p   nul terminate character string to evaluate.
   * \return the number of columns used to display the text.
   */
  inline uint16_t getTextColumns(uint8_t z, const char *p) { return(z < _numZones && p != nullptr ? _Z[z].getTextWidth((uint8_t *)p) : 0); }

 /**
   * Get the value of specified display effect.
   *
   * The display effect is one of the zoneEffect_t types. The returned value will be
   * true if the attribute is set, false if the attribute is not set.
   *
   * \param z   zone number.
   * \param ze  the required text alignment.
   * \return true if the value is set, false otherwise.
   */
  inline boolean getZoneEffect(uint8_t z, zoneEffect_t ze) { return (z < _numZones ? _Z[z].getZoneEffect(ze) : false); }

  /**
   * Set the inter-character spacing in columns for all zones.
   *
   * Set the number of blank columns between characters when they are displayed.
   *
   * \param cs  space between characters in columns.
   */
  void setCharSpacing(uint8_t cs) { for (uint8_t i = 0; i < _numZones; i++) _Z[i].setCharSpacing(cs); }

  /**
   * Set the inter-character spacing in columns for the specified zone.
   *
   * See comments for the 'all zones' variant of this method.
   *
   * \param z   zone number.
   * \param cs  space between characters in columns.
   */
  inline void setCharSpacing(uint8_t z, uint8_t cs) { if (z < _numZones) _Z[z].setCharSpacing(cs); }

  /**
   * Set the display brightness for all the zones.
   *
   * Set the intensity (brightness) of the display.
   *
   * \param intensity the intensity to set the display (0-15).
   */
  inline void setIntensity(uint8_t intensity) { for (uint8_t i = 0; i < _numZones; i++) _Z[i].setIntensity(intensity); }

  /**
   * Set the display brightness for the specified zone.
   *
   * See comments for the 'all zones' variant of this method.
   *
   * \param z   zone number.
   * \param intensity the intensity to set the display (0-15).
   */
  inline void setIntensity(uint8_t z, uint8_t intensity) { if (z < _numZones) _Z[z].setIntensity(intensity); }

  /**
   * Invert the display in all the zones.
   *
   * Set the display to inverted (ON LED turns OFF and vice versa).
   *
   * \param invert  true for inverted display, false for normal display
   */
  inline void setInvert(uint8_t invert) { for (uint8_t i = 0; i < _numZones; i++) _Z[i].setInvert(invert); }

  /**
   * Invert the display in the specified zone.
   *
   * See comments for the 'all zones' variant of this method.
   *
   * \param z   zone number.
   * \param invert  true for inverted display, false for normal display
   */
  inline void setInvert(uint8_t z, uint8_t invert) { if (z < _numZones) _Z[z].setInvert(invert); }

  /**
   * Set the pause between ENTER and EXIT animations for all zones.
   *
   * Between each entry and exit, the library will pause by the number of milliseconds
   * specified to allow the viewer to read the message. For continuous scrolling displays
   * this should be set to the same value as the display speed.
   *
   * \param pause the time, in milliseconds, between animations.
   */
  inline void setPause(uint16_t pause) { for (uint8_t i = 0; i < _numZones; i++) _Z[i].setPause(pause); }

  /**
   * Set the pause between ENTER and EXIT animations for the specified zone.
   *
   * See comments for the 'all zones' variant of this method.
   *
   * \param z   zone number.
   * \param pause the time, in milliseconds, between animations.
   */
  inline void setPause(uint8_t z, uint16_t pause) { if (z < _numZones) _Z[z].setPause(pause); }

  /**
   * Set the horizontal scrolling distance between messages for all the zones.
   *
   * When scrolling horizontally, the distance between the end of one message and the
   * start of the next can be set using this method. Default behavior is for the message
   * to be fully off the display before the new message starts.
   * Set to zero for default behavior.
   *
   * \param space the spacing, in columns, between messages; zero for default behaviour..
   */
  inline void setScrollSpacing(uint16_t space) { for (uint8_t i = 0; i < _numZones; i++) _Z[i].setScrollSpacing(space); }

  /**
   * Set identical IN and OUT animation frame speed for all zones.
   *
   * The speed of the display is the 'tick' time between animation frames. The lower this time
   * the faster the animation; set it to zero to run as fast as possible.
   * 
   * This method sets the IN and OUT animation speeds to be the same.
   *
   * \param speed the time, in milliseconds, between animation frames.
   */
  inline void setSpeed(uint16_t speed) { for (uint8_t i = 0; i < _numZones; i++) _Z[i].setSpeed(speed); }

  /**
   * Set separate IN and OUT animation frame speed for all zones.
   *
   * The speed of the display is the 'tick' time between animation frames. The lower this time
   * the faster the animation; set it to zero to run as fast as possible.
   * 
   * This method allows the IN and OUT animation speeds to be different.
   *
   * \param speedIn the time, in milliseconds, between IN animation frames.
   * \param speedOut the time, in milliseconds, between OUT animation frames.
   */
  inline void setSpeedInOut(uint16_t speedIn, uint16_t speedOut) { for (uint8_t i = 0; i < _numZones; i++) _Z[i].setSpeedInOut(speedIn, speedOut); }

  /**
   * Set the identical IN and OUT animation frame speed for the specified zone.
   *
   * See comments for the 'all zones' variant of this method.
   *
   * \param z   zone number.
   * \param speed the time, in milliseconds, between animation frames.
   */
  inline void setSpeed(uint8_t z, uint16_t speed) { if (z < _numZones) _Z[z].setSpeed(speed); }

  /**
   * Set the separate IN and OUT animation frame speed for the specified zone.
   *
   * See comments for the 'all zones' variant of this method.
   *
   * \param z   zone number.
   * \param speedIn the time, in milliseconds, between IN animation frames.
   * \param speedOut the time, in milliseconds, between OUT animation frames.
   */
  inline void setSpeedInOut(uint8_t z, uint16_t speedIn, uint16_t speedOut) { if (z < _numZones) _Z[z].setSpeedInOut(speedIn, speedOut); }

#if ENA_SPRITE
  /**
  * Set data for user sprite effects (single zone).
  *
  * This method is used to set up user data needed so that the library can
  * display the sprite ahead of the entry/exit of text when the PA_SPRITE
  * animation type is selected.
  *
  * A sprite is made up of a number of frames that run sequentially to make
  * make the animation on the display. Once the animation reaches the last frame
  * it restarts from the first frame.
  *
  * A sprite is defined similarly to a character in the font table. Each byte
  * is a bit pattern defining a column in the sprite. A frame is xWidth bytes
  * in size and there are xFrames in the animation.
  *
  * \param z zone number.
  * \param inData pointer to the data table defining the entry sprite.
  * \param inWidth the width (in bytes) of each frame of the sprite.
  * \param inFrames the number of frames for the sprite.
  * \param outData pointer to the data table that is inWidth*InFrames in size.
  * \param outWidth the width (in bytes) of each frame of the sprite.
  * \param outFrames the number of frames for the sprite.
  */
  void setSpriteData(uint8_t z, const uint8_t *inData, uint8_t inWidth, uint8_t inFrames,
                                const uint8_t *outData, uint8_t outWidth, uint8_t outFrames)
  { if (z < _numZones) _Z[z].setSpriteData(inData, inWidth, inFrames, outData, outWidth, outFrames); }

  /**
  * Set data for user sprite effect (whole display).
  *
  * See the comments for single zone variant of this method.
  *
  * \param inData pointer to the data table defining the entry sprite.
  * \param inWidth the width (in bytes) of each frame of the sprite.
  * \param inFrames the number of frames for the sprite.
  * \param outData pointer to the data table that is inWidth*InFrames in size.
  * \param outWidth the width (in bytes) of each frame of the sprite.
  * \param outFrames the number of frames for the sprite.
  */
  void setSpriteData(const uint8_t *inData, uint8_t inWidth, uint8_t inFrames,
                     const uint8_t *outData, uint8_t outWidth, uint8_t outFrames)
  { for (uint8_t i = 0; i < _numZones; i++) _Z[i].setSpriteData(inData, inWidth, inFrames, outData, outWidth, outFrames); }

#endif

  /**
   * Set the text alignment for all zones.
   *
   * Text alignment is specified as one of the values in textPosition_t.
   *
   * \param ta  the required text alignment.
   */
  inline void setTextAlignment(textPosition_t ta) { for (uint8_t i = 0; i < _numZones; i++) _Z[i].setTextAlignment(ta); }

  /**
   * Set the text alignment for the specified zone.
   *
   * See comments for the 'all zones' variant of this method.
   *
   * \param z zone number.
   * \param ta  the required text alignment.
   */
  inline void setTextAlignment(uint8_t z, textPosition_t ta) { if (z < _numZones) _Z[z].setTextAlignment(ta); }

  /**
   * Set the pointer to the text buffer.
   *
   * Sets the text buffer to be a pointer to user data. The library does not allocate
   * any memory for the text message, rather it is the calling program that supplies
   * a pointer to a buffer. This reduces memory requirements and offers the flexibility
   * to keep a single buffer or rotate buffers with different messages, all under calling
   * program control, with no library limit to the size or numbers of buffers. The text
   * placed in the buffer must be properly terminated by the NUL ('\0') character or
   * processing will overrun the end of the message.
   *
   * This form of the method assumes one zone only.
   *
   * \param pb  pointer to the text buffer to be used.
   */
  inline void setTextBuffer(const char *pb) { setTextBuffer(0, pb); }

  /**
   * Set the pointer to the text buffer for the specified zone.
   *
   * See comments for the single zone version of this method.
   *
   * \param z zone number.
   * \param pb  pointer to the text buffer to be used.
   */
  inline void setTextBuffer(uint8_t z, const char *pb) { if (z < _numZones) _Z[z].setTextBuffer(pb); }

  /**
   * Set the entry and exit text effects for all zones.
   *
   * The 'in' and 'out' text effects are specified using the textEffect_t enumerated
   * type. If no effect is required, NO_EFFECT should be specified. NO_EFFECT
   * is most useful when no exit effect is required (e.g., when DISSOLVE is used) and
   * the entry effect is sufficient.
   *
   * \param effectIn  the entry effect, one of the textEffect_t enumerated values.
   * \param effectOut the exit effect, one of the textEffect_t enumerated values.
   */
  inline void setTextEffect(textEffect_t effectIn, textEffect_t effectOut) { for (uint8_t i = 0; i < _numZones; i++) _Z[i].setTextEffect(effectIn, effectOut); }

  /**
   * Set the entry and exit text effects for a specific zone.
   *
   * See comments for the 'all zones' variant of this method.
   *
   * \param z     zone number.
   * \param effectIn  the entry effect, one of the textEffect_t enumerated values.
   * \param effectOut the exit effect, one of the textEffect_t enumerated values.
   */
  inline void setTextEffect(uint8_t z, textEffect_t effectIn, textEffect_t effectOut) { if (z < _numZones) _Z[z].setTextEffect(effectIn, effectOut); }

  /**
   * Set the display effect for the specified zone.
   *
   * The display effect is one of the zoneEffect_t types, and this will be set (true) or
   * reset (false) depending on the boolean value. The resulting zone display will be
   * modified as per the required effect.
   *
   * \param z   zone number.
   * \param b   set the value if true, reset the value if false
   * \param ze  the required text alignment.
   */
  inline void setZoneEffect(uint8_t z, boolean b, zoneEffect_t ze) { if (z < _numZones) _Z[z].setZoneEffect(b, ze); }

  /**
  * Synchronize the start of zone animations.
  *
  * When zones are set up, the animation start time will default
  * to the set-up time. If several zones need to be animated
  * in synchronized fashion (eg, they are visually stacked vertically),
  * this method will ensure that all the zones start at the same instant.
  * The method should be invoked before the call to displayAnimate().
  */
  inline void synchZoneStart(void) { for (uint8_t i = 1; i < _numZones; i++) _Z[i].setSynchTime(_Z[0].getSynchTime()); }

/** @} */
  //--------------------------------------------------------------
  /** \name Support methods for fonts and characters.
   * @{
   */

  /**
   * Add a user defined character to the replacement list for all zones.
   *
   * Add a replacement characters to the user defined list. The character data must be
   * the same as for a single character in the font definition file. If a character is
   * specified with a code the same as an existing character the existing data will be
   * substituted for the new data. A character code of 0 ('\0') is illegal as this
   * denotes the end of string character for C++ and cannot be used in an actual string.
   *
   * The library does not copy the data definition but only retains a pointer to the data,
   * so any changes to the data storage in the calling program will be reflected into the
   * library. The data must also remain in scope while it is being used.
   *
   * \param code  code for the character data.
   * \param data  pointer to the character data.
   */
  inline void addChar(uint16_t code, const uint8_t *data) { for (uint8_t i = 0; i < _numZones; i++) _Z[i].addChar(code, data); }

  /**
   * Add a user defined character to the replacement specified zone.
   *
   * See the comments for the 'all zones' variant of this method
   *
   * \param z   zone specified
   * \param code  ASCII code for the character data.
   * \param data  pointer to the character data.
   * \return true of the character was inserted in the substitution list.
   */
  inline bool addChar(uint8_t z, uint16_t code, const uint8_t *data) { return(z < _numZones ? _Z[z].addChar(code, data) : false); }

  /**
   * Delete a user defined character to the replacement list for all zones.
   *
   * Delete a reference to a replacement character in the user defined list.
   *
   * \param code  ASCII code for the character data.
   */
  inline void delChar(uint16_t code) { for (uint8_t i = 0; i < _numZones; i++) _Z[i].delChar(code); }

  /**
   * Delete a user defined character to the replacement list for the specified zone.
   *
   * See the comments for the 'all zones' variant of this method.
   *
   * \param z   zone specified
   * \param code  ASCII code for the character data.
   * \return true of the character was found in the substitution list.
   */
  inline bool delChar(uint8_t z, uint16_t code) { return(z < _numZones ? _Z[z].delChar(code) : false); }

  /**
   * Get the display font for specified zone.
   *
   * Get the current font table pointer for the specified zone.
   *
   * \param z specified zone.
   * \return Pointer to the font definition used.
   */
  inline MD_MAX72XX::fontType_t* getFont(uint8_t z) { if (z < _numZones) return (_Z[z].getZoneFont()); else return(nullptr); };

  /**
   * Get the display font for single zone display.
   *
   * Return the current font table pointer for single zone displays.
   *
   * \return Pointer to the font definition used.
   */
  inline MD_MAX72XX::fontType_t* getFont(void) { return(getFont(0)); };

  /**
   * Set the display font for all zones.
   *
   * Set the display font to a user defined font table. This can be created using the
   * MD_MAX72xx font builder (refer to documentation for the tool and the MD_MAX72xx library).
   * Passing nullptr resets to the library default font.
   *
   * \param fontDef Pointer to the font definition to be used.
   */
  inline void setFont(MD_MAX72XX::fontType_t *fontDef) { for (uint8_t i = 0; i < _numZones; i++) _Z[i].setZoneFont(fontDef); }

  /**
   * Set the display font for a specific zone.
   *
   * Set the display font to a user defined font table. This can be created using the
   * MD_MAX72xx font builder (refer to documentation for the tool and the MD_MAX72xx library).
   * Passing nullptr resets to the library default font.
   *
   * \param z   specified zone.
   * \param fontDef Pointer to the font definition to be used.
   */
  inline void setFont(uint8_t z, MD_MAX72XX::fontType_t *fontDef) { if (z < _numZones) _Z[z].setZoneFont(fontDef); }

  /** @} */

#if ENA_GRAPHICS
  //--------------------------------------------------------------
  /** \name Support methods for graphics.
  * @{
  */
  /**
  * Get a pointer to the instantiated graphics object.
  *
  * Provides a pointer to the MD_MAX72XX object to allow access to
  * the display graphics functions.
  *
  * \return Pointer to the MD_MAX72xx object used by the library.
  */
  inline MD_MAX72XX *getGraphicObject(void) { return(&_D); }

  /**
  * Get the start and end column numbers for the whole display.
  *
  * Returns the start and end column numbers for the matrix display.
  * This retains consistency between user code and library.
  *
  * \param startColumn the by-reference parameter that will hold the return value for the start column.
  * \param endColumn the by-reference parameter that will hold the return value for the end column.
  */
  inline void getDisplayExtent(uint16_t &startColumn, uint16_t &endColumn) { startColumn = ZONE_START_COL(0); endColumn = ZONE_END_COL(_numModules-1); }

  /**
  * Get the start and end column numbers for the required zone.
  *
  * Returns the start and end column numbers for the zone display.
  * This retains consistency between user code and library.
  * The by-reference parameters remain unchanged if an invalid zone
  * number is requested.
  *
  * \param z zone specified
  * \param startColumn the by-reference parameter that will hold the return value for the start column.
  * \param endColumn the by-reference parameter that will hold the return value for the end column.
  */
  inline void getDisplayExtent(uint8_t z, uint16_t &startColumn, uint16_t &endColumn) { if (z < _numZones) _Z[z].getZoneExtent(startColumn, endColumn); }

  /**
  * Get the start and end column numbers for the text displayed.
  *
  * Returns the start and end column numbers for the text displayed in zone 0.
  * This can be used for simplicity when the display is a single zone.
  *
  * \param startColumn the by-reference parameter that will hold the return value for the start column.
  * \param endColumn the by-reference parameter that will hold the return value for the end column.
  */
  inline void getTextExtent(uint16_t &startColumn, uint16_t &endColumn) { getTextExtent(0, startColumn, endColumn); }

  /**
  * Get the start and end column numbers for the text displayed.
  *
  * Returns the start and end column numbers for the text displayed in the zone.
  * This retains consistency between user code and library.
  *
  * \param z zone specified
  * \param startColumn the by-reference parameter that will hold the return value for the start column.
  * \param endColumn the by-reference parameter that will hold the return value for the end column.
  */
  inline void getTextExtent(uint8_t z, uint16_t &startColumn, uint16_t &endColumn) { if (z < _numZones) _Z[z].getTextExtent(startColumn, endColumn); }
  /** @} */
#endif

  //--------------------------------------------------------------
  /** \name Support methods for Print class extension.
  * @{
  */

  /**
  * Write a single character to the output display
  *
  * Display a character when given the ASCII code for it. The character is
  * converted to a string and the string printing function invoked.
  * The LED display is designed for string based output, so it does not make much
  * sense to do this. Creating the short string is a consistent way to way to handle
  * single the character.
  *
  * \param c  ASCII code for the character to write.
  * \return the number of characters written.
  */
  virtual size_t write(uint8_t c) { char sz[2]; sz[0] = c; sz[1] = '\0'; write(sz); return(1); }

  /**
  * Write a nul terminated string to the output display.
  *
  * Display a nul terminated string when given a pointer to the char array.
  * Invokes an animation using PA_PRINT with all other settings (alignment,
  * speed, etc) taken from current defaults.
  * This method also invokes the animation for the print and returns when that has
  * finished, so it blocks while the printing is happening, which should be at least
  * one iteration of the wait loop.
  *
  * \param str  Pointer to the nul terminated char array.
  * \return the number of characters written.
  */
  virtual size_t write(const char *str);

  /**
  * Write a character buffer to the output display.
  *
  * Display a non-nul terminated string given a pointer to the buffer and
  * the size of the buffer. The buffer is turned into a nul terminated string
  * and the simple write() method is invoked. Memory is allocated and freed
  * in this method to copy the string.
  *
  * \param buffer Pointer to the data buffer.
  * \param size The number of bytes to write.
  * \return the number of bytes written.
  */
  virtual size_t write(const uint8_t *buffer, size_t size);

  /** @} */

  private:
  // The display hardware controlled by this library
  MD_MAX72XX  _D;         ///< Hardware library object
#if STATIC_ZONES
  MD_PZone    _Z[MAX_ZONES];  ///< Fixed number of zones - static zone allocation
#else
  MD_PZone    *_Z;            ///< Zones buffers - dynamic zone allocation
#endif
  uint8_t     _numModules;///< Number of display modules [0..numModules-1]
  uint8_t     _numZones;  ///< Max number of zones in the display [0..numZones-1]
};

