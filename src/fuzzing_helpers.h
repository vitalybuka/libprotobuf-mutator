// Copyright 2017 Google Inc. All rights reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef FUZZING_HELPERS_H_
#define FUZZING_HELPERS_H_

#include "protobuf_mutator.h"

namespace protobuf_mutator {

// Parses proto from text same way as |MutateTextMessage|.
// libFuzzer expects user will define LLVMFuzzerTestOneInput and
// LLVMFuzzerCustomMutator. It's important that both of them use same
// serialization format.
void ParseTextMessage(const uint8_t* data, size_t size,
                      google::protobuf::Message* output);

// Mutates proto serialized as test.
// |prototype| is message of user-defined type which will be used as a
// temporary storage.
size_t MutateTextMessage(uint8_t* data, size_t size, size_t max_size,
                         ProtobufMutator* mutator,
                         google::protobuf::Message* prototype);

}  // namespace protobuf_mutator

#endif  // FUZZING_HELPERS_H_
