/* ====================================================================
 * The Apache Software License, Version 1.1
 *
 * Copyright (c) 2000 The Apache Software Foundation.  All rights
 * reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *
 * 3. The end-user documentation included with the redistribution,
 *    if any, must include the following acknowledgment:
 *       "This product includes software developed by the
 *        Apache Software Foundation (http://www.apache.org/)."
 *    Alternately, this acknowledgment may appear in the software itself,
 *    if and wherever such third-party acknowledgments normally appear.
 *
 * 4. The names "Apache" and "Apache Software Foundation" must
 *    not be used to endorse or promote products derived from this
 *    software without prior written permission. For written
 *    permission, please contact apache@apache.org.
 *
 * 5. Products derived from this software may not be called "Apache",
 *    nor may "Apache" appear in their name, without prior written
 *    permission of the Apache Software Foundation.
 *
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND ANY EXPRESSED OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED.  IN NO EVENT SHALL THE APACHE SOFTWARE FOUNDATION OR
 * ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
 * USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 * ====================================================================
 *
 * This software consists of voluntary contributions made by many
 * individuals on behalf of the Apache Software Foundation.  For more
 * information on the Apache Software Foundation, please see
 * <http://www.apache.org/>.
 */

#include "networkio.h"

ap_status_t ap_set_local_port(struct ap_socket_t *sock, ap_uint32_t port)
{
    if (!sock) {
        return APR_EBADF;
    }
    sock->local_addr->sin_port = htons((short)port);
    return APR_SUCCESS;
}

ap_status_t ap_set_remote_port(struct ap_socket_t *sock, ap_uint32_t port)
{
    if (!sock) {
        return APR_EBADF;
    }
    sock->remote_addr->sin_port = htons((short)port);
    return APR_SUCCESS;
}

ap_status_t ap_get_local_port(ap_uint32_t *port, struct ap_socket_t *sock)
{
    if (!sock) {
        return APR_EBADF;
    }
    *port = ntohs(sock->local_addr->sin_port);
    return APR_SUCCESS;
}

ap_status_t ap_get_remote_port(ap_uint32_t *port, struct ap_socket_t *sock)
{
    if (!sock) {
        return APR_EBADF;
    }
    *port = ntohs(sock->remote_addr->sin_port);
    return APR_SUCCESS;
}

ap_status_t ap_set_local_ipaddr(struct ap_socket_t *sock, const char *addr)
{
    u_long ipaddr;

    if (!sock) {
        return APR_EBADF;
    }
    
    if (!strcmp(addr, APR_ANYADDR)) {
        sock->local_addr->sin_addr.s_addr = htonl(INADDR_ANY);
        return APR_SUCCESS;
    }
    
    ipaddr = inet_addr(addr);
    
    if (ipaddr == -1) {
        return errno;
    }
    
    sock->local_addr->sin_addr.s_addr = ipaddr;
    return APR_SUCCESS;
}

ap_status_t ap_set_remote_ipaddr(struct ap_socket_t *sock, const char *addr)
{
    u_long ipaddr;

    if (!sock) {
        return APR_EBADF;
    }
    
    if (!strcmp(addr, APR_ANYADDR)) {
        sock->remote_addr->sin_addr.s_addr = htonl(INADDR_ANY);
        return APR_SUCCESS;
    }
    
    ipaddr = inet_addr(addr);
    
    if (ipaddr == (u_long)-1) {
        return errno;
    }
    
    sock->remote_addr->sin_addr.s_addr = ipaddr;
    return APR_SUCCESS;
}

ap_status_t ap_get_local_ipaddr(char **addr, const struct ap_socket_t *sock)
{
    if (!sock) {
        return APR_EBADF;
    }

    *addr = ap_pstrdup(sock->cntxt, inet_ntoa(sock->local_addr->sin_addr));
    return APR_SUCCESS;
}

ap_status_t ap_get_remote_ipaddr(char **addr, const struct ap_socket_t *sock)
{
    if (!sock) {
        return APR_EBADF;
    }

    *addr = ap_pstrdup(sock->cntxt, inet_ntoa(sock->remote_addr->sin_addr));
    return APR_SUCCESS;
}


ap_status_t ap_get_local_name(struct sockaddr_in **name, const struct ap_socket_t *sock)
{
    if (!sock) {
        return APR_EBADF;
    }

    *name = sock->local_addr;
    return APR_SUCCESS;
}

ap_status_t ap_get_remote_name(struct sockaddr_in **name, const struct ap_socket_t *sock)
{
    if (!sock) {
        return APR_EBADF;
    }

    *name = sock->remote_addr;
    return APR_SUCCESS;
}
