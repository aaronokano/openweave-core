/*
 *
 *    Copyright (c) 2013-2017 Nest Labs, Inc.
 *    All rights reserved.
 *
 *    Licensed under the Apache License, Version 2.0 (the "License");
 *    you may not use this file except in compliance with the License.
 *    You may obtain a copy of the License at
 *
 *        http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Unless required by applicable law or agreed to in writing, software
 *    distributed under the License is distributed on an "AS IS" BASIS,
 *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *    See the License for the specific language governing permissions and
 *    limitations under the License.
 */

/**
 *    @file
 *      This file implements secure random data initialization and generation functions
 *      for the Weave layer. The implementation is based on the OpenSSL Library functions.
 *      This implementation is used when #WEAVE_CONFIG_RNG_IMPLEMENTATION_OPENSSL
 *      is enabled (1).
 *
 */

#include <string.h>

#include "WeaveCrypto.h"

#if WEAVE_CONFIG_RNG_IMPLEMENTATION_OPENSSL

#include <openssl/rand.h>

namespace nl {
namespace Weave {
namespace Platform {
namespace Security {

WEAVE_ERROR InitSecureRandomDataSource(nl::Weave::Crypto::EntropyFunct entropyFunct, uint16_t entropyLen, const uint8_t *personalizationData, uint16_t perDataLen)
{
    if (perDataLen > 0)
    {
        if (personalizationData == NULL)
            return WEAVE_ERROR_INVALID_ARGUMENT;

        RAND_seed(personalizationData, perDataLen);
    }

    return WEAVE_NO_ERROR;
}

WEAVE_ERROR GetSecureRandomData(uint8_t *buf, uint16_t len)
{
    if (RAND_bytes((unsigned char *)buf, (int)len) != 1)
        return WEAVE_ERROR_RANDOM_DATA_UNAVAILABLE;

    return WEAVE_NO_ERROR;
}

} // namespace Platform
} // namespace Security
} // namespace Weave
} // namespace nl

#endif // WEAVE_CONFIG_RNG_IMPLEMENTATION_OPENSSL
