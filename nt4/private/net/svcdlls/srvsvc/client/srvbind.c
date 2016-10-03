/*++

Copyright (c) 1990  Microsoft Corporation

Module Name:

    srvbind.c

Abstract:

    Contains the RPC bind and un-bind routines for the Server
    Service.

Author:

    Dan Lafferty (danl)     01-Mar-1991

Environment:

    User Mode -Win32

Revision History:

    01-Mar-1991     danl
        created
    07-Jun-1991 JohnRo
        Allowed debug output of failures.

--*/

//
// INCLUDES
//
#include <nt.h>      // DbgPrint prototype
#include <rpc.h>        // DataTypes and runtime APIs
#include <srvsvc.h>     // generated by the MIDL complier
#include <rpcutil.h>    // NetRpc utils
#include <netlib.h>     // UNUSED macro
#include <srvnames.h>   // SERVER_INTERFACE_NAME



handle_t
SRVSVC_HANDLE_bind (
    SRVSVC_HANDLE   ServerName)

/*++

Routine Description:
    This routine calls a common bind routine that is shared by all services.
    This routine is called from the server service client stubs when
    it is necessary to bind to a server.

Arguments:

    ServerName - A pointer to a string containing the name of the server
        to bind with.

Return Value:

    The binding handle is returned to the stub routine.  If the
    binding is unsuccessful, a NULL will be returned.

--*/
{
    handle_t    bindingHandle;
    RPC_STATUS  status;

    status = NetpBindRpc (
                ServerName,
                SERVER_INTERFACE_NAME,
                TEXT("Security=Impersonation Dynamic False"),
                &bindingHandle);

    return( bindingHandle);
}



void
SRVSVC_HANDLE_unbind (
    SRVSVC_HANDLE   ServerName,
    handle_t        BindingHandle)

/*++

Routine Description:

    This routine calls a common unbind routine that is shared by
    all services.
    This routine is called from the server service client stubs when
    it is necessary to unbind to a server.


Arguments:

    ServerName - This is the name of the server from which to unbind.

    BindingHandle - This is the binding handle that is to be closed.

Return Value:

    none.

--*/
{
    UNUSED(ServerName);     // This parameter is not used

    NetpUnbindRpc ( BindingHandle);
    return;
}