// SPDX-License-Identifier: MIT
// SPDX-FileCopyrightText: 2024 NeoFOAM authors

#pragma once

#ifdef NeoFOAM_USE_DLL
#ifdef NeoFOAM_USE_API_EXPORT
#define NeoFOAM_API __declspec(dllexport)
#else
#define NeoFOAM_API __declspec(dllimport)
#endif
#else
#define NeoFOAM_API
#endif
