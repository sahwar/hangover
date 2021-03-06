/*
 * Copyright 2017 Stefan Dösinger for CodeWeavers
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA
 */

/* NOTE: The guest side uses mingw's headers. The host side uses Wine's headers. */

#include <windows.h>
#include <stdio.h>

#include "windows-user-services.h"
#include "dll_list.h"
#include "qemu_secur32.h"

#ifdef QEMU_DLL_GUEST

BOOL WINAPI DllMainCRTStartup(HMODULE mod, DWORD reason, void *reserved)
{
    return TRUE;
}

#else

#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_secur32);

const struct qemu_ops *qemu_ops;

static const syscall_handler dll_functions[] =
{
    qemu_AcceptSecurityContext,
    qemu_AcquireCredentialsHandle,
    qemu_AcquireCredentialsHandle,
    qemu_AddCredentialsA,
    qemu_AddCredentialsW,
    qemu_AddSecurityPackageA,
    qemu_AddSecurityPackageW,
    qemu_ApplyControlToken,
    qemu_CompleteAuthToken,
    qemu_DecryptMessage,
    qemu_DeleteSecurityContext,
    qemu_EncryptMessage,
    qemu_EnumerateSecurityPackagesA,
    qemu_EnumerateSecurityPackagesW,
    qemu_ExportSecurityContext,
    qemu_FreeContextBuffer,
    qemu_FreeCredentialsHandle,
    qemu_GetComputerObjectNameA,
    qemu_GetComputerObjectNameW,
    qemu_GetUserNameExA,
    qemu_GetUserNameExW,
    qemu_ImpersonateSecurityContext,
    qemu_ImportSecurityContextA,
    qemu_ImportSecurityContextW,
    qemu_InitializeSecurityContext,
    qemu_InitializeSecurityContext,
    qemu_InitSecurityInterfaceA,
    qemu_InitSecurityInterfaceW,
    qemu_LsaCallAuthenticationPackage,
    qemu_LsaConnectUntrusted,
    qemu_LsaDeregisterLogonProcess,
    qemu_LsaEnumerateLogonSessions,
    qemu_LsaFreeReturnBuffer,
    qemu_LsaGetLogonSessionData,
    qemu_LsaLogonUser,
    qemu_LsaLookupAuthenticationPackage,
    qemu_LsaRegisterLogonProcess,
    qemu_MakeSignature,
    qemu_QueryContextAttributes,
    qemu_QueryContextAttributes,
    qemu_QueryCredentialsAttributes,
    qemu_QueryCredentialsAttributes,
    qemu_QuerySecurityContextToken,
    qemu_QuerySecurityPackageInfoA,
    qemu_QuerySecurityPackageInfoW,
    qemu_RevertSecurityContext,
    qemu_SetContextAttributesA,
    qemu_SetContextAttributesW,
    qemu_TranslateNameA,
    qemu_TranslateNameW,
    qemu_VerifySignature,
};

const WINAPI syscall_handler *qemu_dll_register(const struct qemu_ops *ops, uint32_t *dll_num)
{
    WINE_TRACE("Loading host-side secur32 wrapper.\n");

    qemu_ops = ops;
    *dll_num = QEMU_CURRENT_DLL;

    return dll_functions;
}

#endif
