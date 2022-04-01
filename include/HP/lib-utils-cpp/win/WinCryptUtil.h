// (c) Copyright 2021 HP Development Company, L.P.

#pragma once

#include <windows.h>
#include <Wincrypt.h>
#include <string>
#include <memory>
#include <functional>

namespace HP {
namespace Utils {
    class CryptUtil
    {
    public:
        static bool hasValidCertificate(const std::wstring& path);
        static std::string getCertificate(const uint16_t port);
        static std::string getCertificate(const std::wstring& path);
        static std::wstring getCertificateIssuer(const std::wstring& path);
        static std::wstring getCertificateIssuer(const uint16_t port);
        static std::wstring getCertificateSubject(const std::wstring& path);
        static std::wstring getCertificateSubject(const uint16_t port);
        static std::string getCertificateThumbprint(const std::wstring& path);
        static std::string getCertificateThumbprint(const uint16_t port);
        static std::string calculateCertificateThumbprint(const std::string& certificate);

    private:
        static std::unique_ptr<const CERT_CONTEXT, std::function<void(const CERT_CONTEXT*)>> getCertificateContextPtr(const std::wstring& path);
        static std::wstring getCertificateAttribute(PCCERT_CONTEXT pCertContext, DWORD dwFlags);
        static std::string certificateSHA1(const BYTE* bytes, DWORD length);
    };
}
}
