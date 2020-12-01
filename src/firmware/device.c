//	Copyright (C) 2020 Michael McMaster <michael@codesrc.com>
//
//	This file is part of SCSI2SD.
//
//	SCSI2SD is free software: you can redistribute it and/or modify
//	it under the terms of the GNU General Public License as published by
//	the Free Software Foundation, either version 3 of the License, or
//	(at your option) any later version.
//
//	SCSI2SD is distributed in the hope that it will be useful,
//	but WITHOUT ANY WARRANTY; without even the implied warranty of
//	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//	GNU General Public License for more details.
//
//	You should have received a copy of the GNU General Public License
//	along with SCSI2SD.  If not, see <http://www.gnu.org/licenses/>.
#include "device.h"

#include "sd.h"

#include <stddef.h>

S2S_Target* s2s_DeviceFindByScsiId(int scsiId)
{
	int deviceCount;
	S2S_Device* devices = s2s_GetDevices(&deviceCount);
	for (int deviceIdx = 0; deviceIdx < deviceCount; ++deviceIdx)
	{
		int targetCount;
		S2S_Target* targets = devices[deviceIdx].getTargets(devices + deviceIdx, &targetCount);
		for (int targetIdx = 0; targetIdx < targetCount; ++targetIdx)
		{
			S2S_Target* target = targets + targetIdx;
			if (target &&
				(target->cfg->scsiId & S2S_CFG_TARGET_ENABLED) &&
				((target->cfg->scsiId & 7) == scsiId))
			{
				return target;
			}
		}
	}

	return NULL;
}

S2S_Device* s2s_GetDevices(int* count)
{
	*count = 1;
	return sdDevice;
}

