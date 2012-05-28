/*
Copyright (C) 2008-2012 Vana Development Team

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; version 2
of the License.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/
#include "AbstractConnection.h"
#include "ConnectionAcceptor.h"
#include "ExitCodes.h"
#include "Session.h"
#include <functional>

ConnectionAcceptor::ConnectionAcceptor(boost::asio::io_service &ioService, const tcp::endpoint &endpoint, AbstractConnectionFactory *apf, const LoginConfig &loginConfig, bool isServer, const string &patchLocation) :
	m_acceptor(ioService, endpoint),
	m_apf(apf),
	m_sessionManager(new SessionManager),
	m_patchLocation(patchLocation),
	m_loginConfig(loginConfig),
	m_isServer(isServer)
{
	startAccepting();
}

void ConnectionAcceptor::stop() {
	m_acceptor.close();
	m_sessionManager->stopAll();
}

void ConnectionAcceptor::startAccepting() {
	bool ping = (m_isServer ? m_loginConfig.serverPing : m_loginConfig.clientPing);
	try {
		SessionPtr newSession(new Session(m_acceptor.get_io_service(), m_sessionManager, m_apf->createConnection(), true, m_loginConfig.clientEncryption || m_isServer, ping, m_patchLocation));
		m_acceptor.async_accept(newSession->getSocket(), std::bind(&ConnectionAcceptor::handleConnection, this, newSession, std::placeholders::_1));
	}
	catch (std::exception &ex) {
		std::cerr << "[ERROR] Could not start accepting socket on port " << m_acceptor.local_endpoint().port() << ": " << ex.what() << std::endl;
		std::cerr << "Press enter to quit." << std::endl;
		getchar();
		exit(ExitCodes::ListenError);
	}
}

void ConnectionAcceptor::handleConnection(SessionPtr newSession, const boost::system::error_code &error) {
	if (!error) {
		newSession->start();
		startAccepting();
	}
}