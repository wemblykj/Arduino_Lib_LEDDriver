/* IController interface
 * Paul Wightmore 2015
 */
#ifndef _ICONTROLLER_h
#define _ICONTROLLER_h

namespace LEDDriver {

class IController
{
public:
  virtual void reset() = 0;
};

} // namespace LEDDriver

#endif // _ICONTROLLER_h