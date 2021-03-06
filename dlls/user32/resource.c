/*
 * Copyright 2017 André Hentschel
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
#include "qemu_user32.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_user32);
#endif


struct qemu_LoadAcceleratorsW
{
    struct qemu_syscall super;
    uint64_t instance;
    uint64_t name;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI HACCEL WINAPI LoadAcceleratorsW(HINSTANCE instance, LPCWSTR name)
{
    struct qemu_LoadAcceleratorsW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_LOADACCELERATORSW);
    call.instance = (ULONG_PTR)instance;
    call.name = (ULONG_PTR)name;

    qemu_syscall(&call.super);

    return (HACCEL)(ULONG_PTR)call.super.iret;
}

#else

void qemu_LoadAcceleratorsW(struct qemu_syscall *call)
{
    struct qemu_LoadAcceleratorsW *c = (struct qemu_LoadAcceleratorsW *)call;
    HINSTANCE instance;
    WINE_TRACE("\n");

    instance = qemu_ops->qemu_module_g2h(c->instance);

    c->super.iret = (ULONG_PTR)LoadAcceleratorsW(instance, QEMU_G2H(c->name));
}

#endif

struct qemu_LoadAcceleratorsA
{
    struct qemu_syscall super;
    uint64_t instance;
    uint64_t lpTableName;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI HACCEL WINAPI LoadAcceleratorsA(HINSTANCE instance,LPCSTR lpTableName)
{
    struct qemu_LoadAcceleratorsA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_LOADACCELERATORSA);
    call.instance = (ULONG_PTR)instance;
    call.lpTableName = (ULONG_PTR)lpTableName;

    qemu_syscall(&call.super);

    return (HACCEL)(ULONG_PTR)call.super.iret;
}

#else

void qemu_LoadAcceleratorsA(struct qemu_syscall *call)
{
    struct qemu_LoadAcceleratorsA *c = (struct qemu_LoadAcceleratorsA *)call;
    HINSTANCE instance;
    WINE_TRACE("\n");

    instance = qemu_ops->qemu_module_g2h(c->instance);

    c->super.iret = (ULONG_PTR)LoadAcceleratorsA(instance, QEMU_G2H(c->lpTableName));
}

#endif

struct qemu_CopyAcceleratorTableA
{
    struct qemu_syscall super;
    uint64_t src;
    uint64_t dst;
    uint64_t count;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI INT WINAPI CopyAcceleratorTableA(HACCEL src, LPACCEL dst, INT count)
{
    struct qemu_CopyAcceleratorTableA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_COPYACCELERATORTABLEA);
    call.src = (ULONG_PTR)src;
    call.dst = (ULONG_PTR)dst;
    call.count = (ULONG_PTR)count;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CopyAcceleratorTableA(struct qemu_syscall *call)
{
    struct qemu_CopyAcceleratorTableA *c = (struct qemu_CopyAcceleratorTableA *)call;
    WINE_TRACE("\n");
    c->super.iret = CopyAcceleratorTableA(QEMU_G2H(c->src), QEMU_G2H(c->dst), c->count);
}

#endif

struct qemu_CopyAcceleratorTableW
{
    struct qemu_syscall super;
    uint64_t src;
    uint64_t dst;
    uint64_t count;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI INT WINAPI CopyAcceleratorTableW(HACCEL src, LPACCEL dst, INT count)
{
    struct qemu_CopyAcceleratorTableW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_COPYACCELERATORTABLEW);
    call.src = (ULONG_PTR)src;
    call.dst = (ULONG_PTR)dst;
    call.count = (ULONG_PTR)count;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CopyAcceleratorTableW(struct qemu_syscall *call)
{
    struct qemu_CopyAcceleratorTableW *c = (struct qemu_CopyAcceleratorTableW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CopyAcceleratorTableW(QEMU_G2H(c->src), QEMU_G2H(c->dst), c->count);
}

#endif

struct qemu_CreateAcceleratorTableA
{
    struct qemu_syscall super;
    uint64_t lpaccel;
    uint64_t count;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI HACCEL WINAPI CreateAcceleratorTableA(LPACCEL lpaccel, INT count)
{
    struct qemu_CreateAcceleratorTableA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CREATEACCELERATORTABLEA);
    call.lpaccel = (ULONG_PTR)lpaccel;
    call.count = (ULONG_PTR)count;

    qemu_syscall(&call.super);

    return (HACCEL)(ULONG_PTR)call.super.iret;
}

#else

void qemu_CreateAcceleratorTableA(struct qemu_syscall *call)
{
    struct qemu_CreateAcceleratorTableA *c = (struct qemu_CreateAcceleratorTableA *)call;
    WINE_TRACE("\n");
    c->super.iret = (ULONG_PTR)CreateAcceleratorTableA(QEMU_G2H(c->lpaccel), c->count);
}

#endif

struct qemu_CreateAcceleratorTableW
{
    struct qemu_syscall super;
    uint64_t lpaccel;
    uint64_t count;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI HACCEL WINAPI CreateAcceleratorTableW(LPACCEL lpaccel, INT count)
{
    struct qemu_CreateAcceleratorTableW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CREATEACCELERATORTABLEW);
    call.lpaccel = (ULONG_PTR)lpaccel;
    call.count = (ULONG_PTR)count;

    qemu_syscall(&call.super);

    return (HACCEL)(ULONG_PTR)call.super.iret;
}

#else

void qemu_CreateAcceleratorTableW(struct qemu_syscall *call)
{
    struct qemu_CreateAcceleratorTableW *c = (struct qemu_CreateAcceleratorTableW *)call;
    WINE_TRACE("\n");
    c->super.iret = (ULONG_PTR)CreateAcceleratorTableW(QEMU_G2H(c->lpaccel), c->count);
}

#endif

struct qemu_DestroyAcceleratorTable
{
    struct qemu_syscall super;
    uint64_t handle;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI DestroyAcceleratorTable(HACCEL handle)
{
    struct qemu_DestroyAcceleratorTable call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DESTROYACCELERATORTABLE);
    call.handle = (ULONG_PTR)handle;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_DestroyAcceleratorTable(struct qemu_syscall *call)
{
    struct qemu_DestroyAcceleratorTable *c = (struct qemu_DestroyAcceleratorTable *)call;
    WINE_TRACE("\n");
    c->super.iret = DestroyAcceleratorTable(QEMU_G2H(c->handle));
}

#endif

struct qemu_LoadStringW
{
    struct qemu_syscall super;
    uint64_t instance;
    uint64_t resource_id;
    uint64_t buffer;
    uint64_t buflen;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI INT WINAPI LoadStringW(HINSTANCE instance, UINT resource_id, LPWSTR buffer, INT buflen)
{
    struct qemu_LoadStringW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_LOADSTRINGW);
    call.instance = (ULONG_PTR)instance;
    call.resource_id = (ULONG_PTR)resource_id;
    call.buffer = (ULONG_PTR)buffer;
    call.buflen = (ULONG_PTR)buflen;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_LoadStringW(struct qemu_syscall *call)
{
    struct qemu_LoadStringW *c = (struct qemu_LoadStringW *)call;
    HINSTANCE instance;
    WINE_TRACE("\n");

    instance = qemu_ops->qemu_module_g2h(c->instance);

    c->super.iret = LoadStringW(instance, c->resource_id, QEMU_G2H(c->buffer), c->buflen);
}

#endif

struct qemu_LoadStringA
{
    struct qemu_syscall super;
    uint64_t instance;
    uint64_t resource_id;
    uint64_t buffer;
    uint64_t buflen;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI INT WINAPI LoadStringA(HINSTANCE instance, UINT resource_id, LPSTR buffer, INT buflen)
{
    struct qemu_LoadStringA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_LOADSTRINGA);
    call.instance = (ULONG_PTR)instance;
    call.resource_id = (ULONG_PTR)resource_id;
    call.buffer = (ULONG_PTR)buffer;
    call.buflen = (ULONG_PTR)buflen;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_LoadStringA(struct qemu_syscall *call)
{
    struct qemu_LoadStringA *c = (struct qemu_LoadStringA *)call;
    HINSTANCE instance;
    WINE_TRACE("\n");

    instance = qemu_ops->qemu_module_g2h(c->instance);

    c->super.iret = LoadStringA(instance, c->resource_id, QEMU_G2H(c->buffer), c->buflen);
}

#endif

struct qemu_GetGuiResources
{
    struct qemu_syscall super;
    uint64_t hProcess;
    uint64_t uiFlags;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI DWORD WINAPI GetGuiResources(HANDLE hProcess, DWORD uiFlags)
{
    struct qemu_GetGuiResources call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETGUIRESOURCES);
    call.hProcess = (ULONG_PTR)hProcess;
    call.uiFlags = (ULONG_PTR)uiFlags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add GetGuiResources to Wine headers? */
extern DWORD WINAPI GetGuiResources(HANDLE hProcess, DWORD uiFlags);
void qemu_GetGuiResources(struct qemu_syscall *call)
{
    struct qemu_GetGuiResources *c = (struct qemu_GetGuiResources *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetGuiResources(QEMU_G2H(c->hProcess), c->uiFlags);
}

#endif

