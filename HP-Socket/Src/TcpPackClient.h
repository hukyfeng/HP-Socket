/*
 * Copyright: JessMA Open Source (ldcsaa@gmail.com)
 *
 * Version	: 3.4.3
 * Author	: Bruce Liang
 * Website	: http://www.jessma.org
 * Project	: https://github.com/ldcsaa
 * Blog		: http://www.cnblogs.com/ldcsaa
 * Wiki		: http://www.oschina.net/p/hp-socket
 * QQ Group	: 75375912
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
 
#pragma once

#include "TcpClient.h"
#include "MiscHelper.h"

class CTcpPackClient : public IPackClient, public CTcpClient
{
public:
	virtual BOOL SendPackets(const WSABUF pBuffers[], int iCount);

protected:
	virtual EnHandleResult FireReceive(IClient* pClient, const BYTE* pData, int iLength);

	virtual BOOL CheckParams();
	virtual void Reset(BOOL bAll = TRUE);

public:
	virtual void SetMaxPackSize		(DWORD dwMaxPackSize)		{m_dwMaxPackSize = dwMaxPackSize;}
	virtual void SetPackHeaderFlag	(USHORT usPackHeaderFlag)	{m_usHeaderFlag  = usPackHeaderFlag;}
	virtual DWORD GetMaxPackSize	()	{return m_dwMaxPackSize;}
	virtual USHORT GetPackHeaderFlag()	{return m_usHeaderFlag;}

private:
	EnHandleResult FireSuperReceive(IClient* pClient, const BYTE* pData, int iLength)
		{return __super::FireReceive(pClient, pData, iLength);}

	friend EnHandleResult ParsePack<>	(CTcpPackClient* pThis, TPackInfo<TItemListEx>* pInfo, TItemListEx* pBuffer, IClient* pSocket,
										DWORD dwMaxPackSize, USHORT usPackHeaderFlag, const BYTE* pData, int iLength);

public:
	CTcpPackClient(ITcpClientListener* psoListener)	: CTcpClient(psoListener)
	, m_dwMaxPackSize	(TCP_PACK_DEFAULT_MAX_SIZE)
	, m_usHeaderFlag	(TCP_PACK_DEFAULT_HEADER_FLAG)
	, m_pkInfo			(nullptr)
	, m_lsBuffer		(m_itPool)
	{

	}

	virtual ~CTcpPackClient()	{if(HasStarted()) Stop();}

private:
	DWORD	m_dwMaxPackSize;
	USHORT	m_usHeaderFlag;

	TPackInfo<TItemListEx>	m_pkInfo;
	TItemListEx				m_lsBuffer;
};
