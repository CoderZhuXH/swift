//===--- SwiftValue.h - Boxed Swift value class -----------------*- C++ -*-===//
//
// This source file is part of the Swift.org open source project
//
// Copyright (c) 2014 - 2016 Apple Inc. and the Swift project authors
// Licensed under Apache License v2.0 with Runtime Library Exception
//
// See http://swift.org/LICENSE.txt for license information
// See http://swift.org/CONTRIBUTORS.txt for the list of Swift project authors
//
//===----------------------------------------------------------------------===//
//
// This implements the Objective-C class that is used to carry Swift values
// that have been bridged to Objective-C objects without special handling.
// The class is opaque to user code, but is `NSObject`- and `NSCopying`-
// conforming and is understood by the Swift runtime for dynamic casting
// back to the contained type.
//
//===----------------------------------------------------------------------===//

#ifndef SWIFT_RUNTIME_SWIFTVALUE_H
#define SWIFT_RUNTIME_SWIFTVALUE_H

#if SWIFT_OBJC_INTEROP
#include <objc/runtime.h>

// SwiftValue is an Objective-C class, but we shouldn't interface with it
// directly as such. Keep the type opaque.
#if __OBJC__
@class SwiftValue;
#else
typedef struct SwiftValue SwiftValue;
#endif

namespace swift {

/// Bridge a Swift value to an Objective-C object by boxing it as a SwiftValue.
SwiftValue *bridgeAnythingToSwiftValueObject(OpaqueValue *src,
                                             const Metadata *srcType,
                                             bool consume);

/// Get the type metadata for a value in a Swift box.
const Metadata *getSwiftValueTypeMetadata(SwiftValue *v);

/// Get the value out of a Swift box along with its type metadata. The value
/// inside the box is immutable and must not be modified or taken from the box.
std::pair<const Metadata *, const OpaqueValue *>
getValueFromSwiftValue(SwiftValue *v);

/// Return the object reference as a SwiftValue* if it is a SwiftValue instance,
/// or nil if it is not.
SwiftValue *getAsSwiftValue(id object);

} // namespace swift
#endif

#endif
