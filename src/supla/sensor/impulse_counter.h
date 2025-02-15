/*
 Copyright (C) AC SOFTWARE SP. Z O.O.

 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 2
 of the License, or (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
*/

#ifndef SRC_SUPLA_SENSOR_IMPULSE_COUNTER_H_
#define SRC_SUPLA_SENSOR_IMPULSE_COUNTER_H_

#include <supla-common/proto.h>
#include <supla/action_handler.h>
#include <supla/channel_element.h>

namespace Supla {

class Io;

namespace Sensor {
class ImpulseCounter : public ChannelElement, public ActionHandler {
 public:
  ImpulseCounter(Supla::Io *io,
                 int _impulsePin,
                 bool _detectLowToHigh = false,
                 bool inputPullup = true,
                 unsigned int _debounceDelay = 10);
  ImpulseCounter(int _impulsePin,
                 bool _detectLowToHigh = false,
                 bool inputPullup = true,
                 unsigned int _debounceDelay = 10);

  void onInit() override;
  void onLoadState() override;
  void onSaveState() override;
  void onFastTimer() override;
  void handleAction(int event, int action) override;
  int handleCalcfgFromServer(TSD_DeviceCalCfgRequest *request) override;
  void iterateAlways() override;

  // Returns value of a counter at given Supla channel
  unsigned _supla_int64_t getCounter();

  // Set counter to a given value
  void setCounter(unsigned _supla_int64_t value);

  // Increment the counter by 1
  void incCounter();

 protected:
  int prevState = 0;  // Store previous state of pin (LOW/HIGH). It is used to
                      // track changes on pin state.
  int impulsePin = -1;  // Pin where impulses are counted

  uint32_t lastImpulseMillis =
      0;  // Stores timestamp of last impulse (used to ignore
          // changes of state during 10 ms timeframe)
  unsigned int debounceDelay = 10;
  bool detectLowToHigh = false;  // defines if we count raining (LOW to HIGH) or
                                 // falling (HIGH to LOW) edge
  bool inputPullup = true;

  unsigned _supla_int64_t counter = 0;  // Actual count of impulses
  uint32_t lastReadTime = 0;
  Supla::Io *io = nullptr;
};

}  // namespace Sensor
}  // namespace Supla

#endif  // SRC_SUPLA_SENSOR_IMPULSE_COUNTER_H_
