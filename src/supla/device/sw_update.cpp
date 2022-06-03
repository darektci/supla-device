/*
 Copyright (C) AC SOFTWARE SP. Z O.O.

 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 2 of the License, or (at your option) any later version.
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 You should have received a copy of the GNU General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
*/

#include "sw_update.h"
#include <string.h>

#if defined(ARDUINO) || defined(SUPLA_TEST) || defined(SUPLA_LINUX) || \
  defined(SUPLA_FREERTOS)
// TODO implement sw update for remaining targets
Supla::Device::SwUpdate* Supla::Device::SwUpdate::Create(
    SuplaDeviceClass *sdc, const char *newUrl) {
  (void)(newUrl);
  (void)(sdc);
  return nullptr;
}
#endif

Supla::Device::SwUpdate::~SwUpdate() {
}

void Supla::Device::SwUpdate::start() {
  started = true;
}

Supla::Device::SwUpdate::SwUpdate(SuplaDeviceClass *sdc, const char *newUrl)
  : sdc(sdc) {
    setUrl(newUrl);
  }

void Supla::Device::SwUpdate::setUrl(const char *newUrl) {
  if (newUrl) {
    strncpy(url, newUrl, SUPLA_MAX_URL_LENGTH);
  }
}

bool Supla::Device::SwUpdate::isStarted() {
  return started;
}

void Supla::Device::SwUpdate::useBeta() {
  beta = true;
}
