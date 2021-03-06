/**
 * Autogenerated by Thrift Compiler (1.0.0-dev)
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#include "zipkinCore_types.h"

#include <algorithm>



int _kAnnotationTypeValues[] = {
  AnnotationType::BOOL,
  AnnotationType::BYTES,
  AnnotationType::I16,
  AnnotationType::I32,
  AnnotationType::I64,
  AnnotationType::DOUBLE,
  AnnotationType::STRING
};
const char* _kAnnotationTypeNames[] = {
  "BOOL",
  "BYTES",
  "I16",
  "I32",
  "I64",
  "DOUBLE",
  "STRING"
};
const std::map<int, const char*> _AnnotationType_VALUES_TO_NAMES(::apache::thrift::TEnumIterator(7, _kAnnotationTypeValues, _kAnnotationTypeNames), ::apache::thrift::TEnumIterator(-1, NULL, NULL));

const char* Endpoint::ascii_fingerprint = "C7D2D58463AC91C552EE8B325EA2ACCC";
const uint8_t Endpoint::binary_fingerprint[16] = {0xC7,0xD2,0xD5,0x84,0x63,0xAC,0x91,0xC5,0x52,0xEE,0x8B,0x32,0x5E,0xA2,0xAC,0xCC};

uint32_t Endpoint::read(::apache::thrift::protocol::TProtocol* iprot) {

  uint32_t xfer = 0;
  std::string fname;
  ::apache::thrift::protocol::TType ftype;
  int16_t fid;

  xfer += iprot->readStructBegin(fname);

  using ::apache::thrift::protocol::TProtocolException;


  while (true)
  {
    xfer += iprot->readFieldBegin(fname, ftype, fid);
    if (ftype == ::apache::thrift::protocol::T_STOP) {
      break;
    }
    switch (fid)
    {
      case 1:
        if (ftype == ::apache::thrift::protocol::T_I32) {
          xfer += iprot->readI32(this->ipv4);
          this->__isset.ipv4 = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 2:
        if (ftype == ::apache::thrift::protocol::T_I16) {
          xfer += iprot->readI16(this->port);
          this->__isset.port = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 3:
        if (ftype == ::apache::thrift::protocol::T_STRING) {
          xfer += iprot->readString(this->service_name);
          this->__isset.service_name = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      default:
        xfer += iprot->skip(ftype);
        break;
    }
    xfer += iprot->readFieldEnd();
  }

  xfer += iprot->readStructEnd();

  return xfer;
}

uint32_t Endpoint::write(::apache::thrift::protocol::TProtocol* oprot) const {
  uint32_t xfer = 0;
  xfer += oprot->writeStructBegin("Endpoint");

  xfer += oprot->writeFieldBegin("ipv4", ::apache::thrift::protocol::T_I32, 1);
  xfer += oprot->writeI32(this->ipv4);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldBegin("port", ::apache::thrift::protocol::T_I16, 2);
  xfer += oprot->writeI16(this->port);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldBegin("service_name", ::apache::thrift::protocol::T_STRING, 3);
  xfer += oprot->writeString(this->service_name);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldStop();
  xfer += oprot->writeStructEnd();
  return xfer;
}

void swap(Endpoint &a, Endpoint &b) {
  using ::std::swap;
  swap(a.ipv4, b.ipv4);
  swap(a.port, b.port);
  swap(a.service_name, b.service_name);
  swap(a.__isset, b.__isset);
}

const char* Annotation::ascii_fingerprint = "A4BFBBE255098BC196C3C976B129CD5A";
const uint8_t Annotation::binary_fingerprint[16] = {0xA4,0xBF,0xBB,0xE2,0x55,0x09,0x8B,0xC1,0x96,0xC3,0xC9,0x76,0xB1,0x29,0xCD,0x5A};

uint32_t Annotation::read(::apache::thrift::protocol::TProtocol* iprot) {

  uint32_t xfer = 0;
  std::string fname;
  ::apache::thrift::protocol::TType ftype;
  int16_t fid;

  xfer += iprot->readStructBegin(fname);

  using ::apache::thrift::protocol::TProtocolException;


  while (true)
  {
    xfer += iprot->readFieldBegin(fname, ftype, fid);
    if (ftype == ::apache::thrift::protocol::T_STOP) {
      break;
    }
    switch (fid)
    {
      case 1:
        if (ftype == ::apache::thrift::protocol::T_I64) {
          xfer += iprot->readI64(this->timestamp);
          this->__isset.timestamp = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 2:
        if (ftype == ::apache::thrift::protocol::T_STRING) {
          xfer += iprot->readString(this->value);
          this->__isset.value = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 3:
        if (ftype == ::apache::thrift::protocol::T_STRUCT) {
          xfer += this->host.read(iprot);
          this->__isset.host = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 4:
        if (ftype == ::apache::thrift::protocol::T_I32) {
          xfer += iprot->readI32(this->duration);
          this->__isset.duration = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      default:
        xfer += iprot->skip(ftype);
        break;
    }
    xfer += iprot->readFieldEnd();
  }

  xfer += iprot->readStructEnd();

  return xfer;
}

uint32_t Annotation::write(::apache::thrift::protocol::TProtocol* oprot) const {
  uint32_t xfer = 0;
  xfer += oprot->writeStructBegin("Annotation");

  xfer += oprot->writeFieldBegin("timestamp", ::apache::thrift::protocol::T_I64, 1);
  xfer += oprot->writeI64(this->timestamp);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldBegin("value", ::apache::thrift::protocol::T_STRING, 2);
  xfer += oprot->writeString(this->value);
  xfer += oprot->writeFieldEnd();

  if (this->__isset.host) {
    xfer += oprot->writeFieldBegin("host", ::apache::thrift::protocol::T_STRUCT, 3);
    xfer += this->host.write(oprot);
    xfer += oprot->writeFieldEnd();
  }
  if (this->__isset.duration) {
    xfer += oprot->writeFieldBegin("duration", ::apache::thrift::protocol::T_I32, 4);
    xfer += oprot->writeI32(this->duration);
    xfer += oprot->writeFieldEnd();
  }
  xfer += oprot->writeFieldStop();
  xfer += oprot->writeStructEnd();
  return xfer;
}

void swap(Annotation &a, Annotation &b) {
  using ::std::swap;
  swap(a.timestamp, b.timestamp);
  swap(a.value, b.value);
  swap(a.host, b.host);
  swap(a.duration, b.duration);
  swap(a.__isset, b.__isset);
}

const char* BinaryAnnotation::ascii_fingerprint = "7673CBCF8AFC8A8C6EF00023E84E022D";
const uint8_t BinaryAnnotation::binary_fingerprint[16] = {0x76,0x73,0xCB,0xCF,0x8A,0xFC,0x8A,0x8C,0x6E,0xF0,0x00,0x23,0xE8,0x4E,0x02,0x2D};

uint32_t BinaryAnnotation::read(::apache::thrift::protocol::TProtocol* iprot) {

  uint32_t xfer = 0;
  std::string fname;
  ::apache::thrift::protocol::TType ftype;
  int16_t fid;

  xfer += iprot->readStructBegin(fname);

  using ::apache::thrift::protocol::TProtocolException;


  while (true)
  {
    xfer += iprot->readFieldBegin(fname, ftype, fid);
    if (ftype == ::apache::thrift::protocol::T_STOP) {
      break;
    }
    switch (fid)
    {
      case 1:
        if (ftype == ::apache::thrift::protocol::T_STRING) {
          xfer += iprot->readString(this->key);
          this->__isset.key = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 2:
        if (ftype == ::apache::thrift::protocol::T_STRING) {
          xfer += iprot->readBinary(this->value);
          this->__isset.value = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 3:
        if (ftype == ::apache::thrift::protocol::T_I32) {
          int32_t ecast0;
          xfer += iprot->readI32(ecast0);
          this->annotation_type = (AnnotationType::type)ecast0;
          this->__isset.annotation_type = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 4:
        if (ftype == ::apache::thrift::protocol::T_STRUCT) {
          xfer += this->host.read(iprot);
          this->__isset.host = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      default:
        xfer += iprot->skip(ftype);
        break;
    }
    xfer += iprot->readFieldEnd();
  }

  xfer += iprot->readStructEnd();

  return xfer;
}

uint32_t BinaryAnnotation::write(::apache::thrift::protocol::TProtocol* oprot) const {
  uint32_t xfer = 0;
  xfer += oprot->writeStructBegin("BinaryAnnotation");

  xfer += oprot->writeFieldBegin("key", ::apache::thrift::protocol::T_STRING, 1);
  xfer += oprot->writeString(this->key);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldBegin("value", ::apache::thrift::protocol::T_STRING, 2);
  xfer += oprot->writeBinary(this->value);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldBegin("annotation_type", ::apache::thrift::protocol::T_I32, 3);
  xfer += oprot->writeI32((int32_t)this->annotation_type);
  xfer += oprot->writeFieldEnd();

  if (this->__isset.host) {
    xfer += oprot->writeFieldBegin("host", ::apache::thrift::protocol::T_STRUCT, 4);
    xfer += this->host.write(oprot);
    xfer += oprot->writeFieldEnd();
  }
  xfer += oprot->writeFieldStop();
  xfer += oprot->writeStructEnd();
  return xfer;
}

void swap(BinaryAnnotation &a, BinaryAnnotation &b) {
  using ::std::swap;
  swap(a.key, b.key);
  swap(a.value, b.value);
  swap(a.annotation_type, b.annotation_type);
  swap(a.host, b.host);
  swap(a.__isset, b.__isset);
}

const char* Span::ascii_fingerprint = "907A6AF2059290FA4FFCF10C7844E12B";
const uint8_t Span::binary_fingerprint[16] = {0x90,0x7A,0x6A,0xF2,0x05,0x92,0x90,0xFA,0x4F,0xFC,0xF1,0x0C,0x78,0x44,0xE1,0x2B};

uint32_t Span::read(::apache::thrift::protocol::TProtocol* iprot) {

  uint32_t xfer = 0;
  std::string fname;
  ::apache::thrift::protocol::TType ftype;
  int16_t fid;

  xfer += iprot->readStructBegin(fname);

  using ::apache::thrift::protocol::TProtocolException;


  while (true)
  {
    xfer += iprot->readFieldBegin(fname, ftype, fid);
    if (ftype == ::apache::thrift::protocol::T_STOP) {
      break;
    }
    switch (fid)
    {
      case 1:
        if (ftype == ::apache::thrift::protocol::T_I64) {
          xfer += iprot->readI64(this->trace_id);
          this->__isset.trace_id = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 3:
        if (ftype == ::apache::thrift::protocol::T_STRING) {
          xfer += iprot->readString(this->name);
          this->__isset.name = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 4:
        if (ftype == ::apache::thrift::protocol::T_I64) {
          xfer += iprot->readI64(this->id);
          this->__isset.id = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 5:
        if (ftype == ::apache::thrift::protocol::T_I64) {
          xfer += iprot->readI64(this->parent_id);
          this->__isset.parent_id = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 6:
        if (ftype == ::apache::thrift::protocol::T_LIST) {
          {
            this->annotations.clear();
            uint32_t _size1;
            ::apache::thrift::protocol::TType _etype4;
            xfer += iprot->readListBegin(_etype4, _size1);
            this->annotations.resize(_size1);
            uint32_t _i5;
            for (_i5 = 0; _i5 < _size1; ++_i5)
            {
              xfer += this->annotations[_i5].read(iprot);
            }
            xfer += iprot->readListEnd();
          }
          this->__isset.annotations = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 8:
        if (ftype == ::apache::thrift::protocol::T_LIST) {
          {
            this->binary_annotations.clear();
            uint32_t _size6;
            ::apache::thrift::protocol::TType _etype9;
            xfer += iprot->readListBegin(_etype9, _size6);
            this->binary_annotations.resize(_size6);
            uint32_t _i10;
            for (_i10 = 0; _i10 < _size6; ++_i10)
            {
              xfer += this->binary_annotations[_i10].read(iprot);
            }
            xfer += iprot->readListEnd();
          }
          this->__isset.binary_annotations = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 9:
        if (ftype == ::apache::thrift::protocol::T_BOOL) {
          xfer += iprot->readBool(this->debug);
          this->__isset.debug = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      default:
        xfer += iprot->skip(ftype);
        break;
    }
    xfer += iprot->readFieldEnd();
  }

  xfer += iprot->readStructEnd();

  return xfer;
}

uint32_t Span::write(::apache::thrift::protocol::TProtocol* oprot) const {
  uint32_t xfer = 0;
  xfer += oprot->writeStructBegin("Span");

  xfer += oprot->writeFieldBegin("trace_id", ::apache::thrift::protocol::T_I64, 1);
  xfer += oprot->writeI64(this->trace_id);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldBegin("name", ::apache::thrift::protocol::T_STRING, 3);
  xfer += oprot->writeString(this->name);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldBegin("id", ::apache::thrift::protocol::T_I64, 4);
  xfer += oprot->writeI64(this->id);
  xfer += oprot->writeFieldEnd();

  if (this->__isset.parent_id) {
    xfer += oprot->writeFieldBegin("parent_id", ::apache::thrift::protocol::T_I64, 5);
    xfer += oprot->writeI64(this->parent_id);
    xfer += oprot->writeFieldEnd();
  }
  xfer += oprot->writeFieldBegin("annotations", ::apache::thrift::protocol::T_LIST, 6);
  {
    xfer += oprot->writeListBegin(::apache::thrift::protocol::T_STRUCT, static_cast<uint32_t>(this->annotations.size()));
    std::vector<Annotation> ::const_iterator _iter11;
    for (_iter11 = this->annotations.begin(); _iter11 != this->annotations.end(); ++_iter11)
    {
      xfer += (*_iter11).write(oprot);
    }
    xfer += oprot->writeListEnd();
  }
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldBegin("binary_annotations", ::apache::thrift::protocol::T_LIST, 8);
  {
    xfer += oprot->writeListBegin(::apache::thrift::protocol::T_STRUCT, static_cast<uint32_t>(this->binary_annotations.size()));
    std::vector<BinaryAnnotation> ::const_iterator _iter12;
    for (_iter12 = this->binary_annotations.begin(); _iter12 != this->binary_annotations.end(); ++_iter12)
    {
      xfer += (*_iter12).write(oprot);
    }
    xfer += oprot->writeListEnd();
  }
  xfer += oprot->writeFieldEnd();

  if (this->__isset.debug) {
    xfer += oprot->writeFieldBegin("debug", ::apache::thrift::protocol::T_BOOL, 9);
    xfer += oprot->writeBool(this->debug);
    xfer += oprot->writeFieldEnd();
  }
  xfer += oprot->writeFieldStop();
  xfer += oprot->writeStructEnd();
  return xfer;
}

void swap(Span &a, Span &b) {
  using ::std::swap;
  swap(a.trace_id, b.trace_id);
  swap(a.name, b.name);
  swap(a.id, b.id);
  swap(a.parent_id, b.parent_id);
  swap(a.annotations, b.annotations);
  swap(a.binary_annotations, b.binary_annotations);
  swap(a.debug, b.debug);
  swap(a.__isset, b.__isset);
}


