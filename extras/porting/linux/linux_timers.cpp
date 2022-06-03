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

#include "linux_timers.h"
#include <supla-common/log.h>
#include <thread>
#include <SuplaDevice.h>
#include <supla/time.h>

void supla10msTimer() {
  while (1) {
    SuplaDevice.onTimer();
    delay(10);
  }
}

void supla1msTimer() {
  while (1) {
    SuplaDevice.onFastTimer();
    delay(1);
  }
}

void Supla::Linux::Timers::init() {
  supla_log(LOG_DEBUG, "Starting linux timers...");
  std::thread standardTimer(supla10msTimer);
  standardTimer.detach();

  std::thread fastTimer(supla1msTimer);
  fastTimer.detach();

}
