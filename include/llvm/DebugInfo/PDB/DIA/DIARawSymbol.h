//===- DIARawSymbol.h - DIA implementation of IPDBRawSymbol ----*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_DEBUGINFO_PDB_DIA_DIARAWSYMBOL_H
#define LLVM_DEBUGINFO_PDB_DIA_DIARAWSYMBOL_H

#include "DIASupport.h"
#include "llvm/DebugInfo/PDB/IPDBRawSymbol.h"

namespace llvm {
class DIASession;
class DIARawSymbol : public IPDBRawSymbol {
public:
  DIARawSymbol(const DIASession &PDBSession, CComPtr<IDiaSymbol> DiaSymbol);

  void dump(raw_ostream &OS, int Indent, PDB_DumpLevel Level) const override;

  CComPtr<IDiaSymbol> getDiaSymbol() const { return Symbol; }

  std::unique_ptr<IPDBEnumSymbols>
  DIARawSymbol::findChildren(PDB_SymType Type) const override;
  std::unique_ptr<IPDBEnumSymbols>
  findChildren(PDB_SymType Type, StringRef Name,
               PDB_NameSearchFlags Flags) const override;
  std::unique_ptr<IPDBEnumSymbols>
  findChildrenByRVA(PDB_SymType Type, StringRef Name, PDB_NameSearchFlags Flags,
                    uint32_t RVA) const override;
  std::unique_ptr<IPDBEnumSymbols>
  findInlineFramesByRVA(uint32_t RVA) const override;

  void getDataBytes(llvm::SmallVector<uint8_t, 32> &bytes) const override;
  void getFrontEndVersion(VersionInfo &Version) const override;
  void getBackEndVersion(VersionInfo &Version) const override;
  PDB_MemberAccess getAccess() const override;
  uint32_t getAddressOffset() const override;
  uint32_t getAddressSection() const override;
  uint32_t getAge() const override;
  uint32_t getArrayIndexTypeId() const override;
  uint32_t getBaseDataOffset() const override;
  uint32_t getBaseDataSlot() const override;
  uint32_t getBaseSymbolId() const override;
  PDB_BuiltinType getBuiltinType() const override;
  uint32_t getBitPosition() const override;
  PDB_CallingConv getCallingConvention() const override;
  uint32_t getClassParentId() const override;
  std::string getCompilerName() const override;
  uint32_t getCount() const override;
  uint32_t getCountLiveRanges() const override;
  PDB_Lang getLanguage() const override;
  uint32_t getLexicalParentId() const override;
  std::string getLibraryName() const override;
  uint32_t getLiveRangeStartAddressOffset() const override;
  uint32_t getLiveRangeStartAddressSection() const override;
  uint32_t getLiveRangeStartRelativeVirtualAddress() const override;
  PDB_RegisterId getLocalBasePointerRegisterId() const override;
  uint32_t getLowerBoundId() const override;
  uint32_t getMemorySpaceKind() const override;
  std::string getName() const override;
  uint32_t getNumberOfAcceleratorPointerTags() const override;
  uint32_t getNumberOfColumns() const override;
  uint32_t getNumberOfModifiers() const override;
  uint32_t getNumberOfRegisterIndices() const override;
  uint32_t getNumberOfRows() const override;
  std::string getObjectFileName() const override;
  uint32_t getOemId() const override;
  uint32_t getOemSymbolId() const override;
  uint32_t getOffsetInUdt() const override;
  PDB_Cpu getPlatform() const override;
  uint32_t getRank() const override;
  PDB_RegisterId getRegisterId() const override;
  uint32_t getRegisterType() const override;
  uint32_t getRelativeVirtualAddress() const override;
  uint32_t getSamplerSlot() const override;
  uint32_t getSignature() const override;
  uint32_t getSizeInUdt() const override;
  uint32_t getSlot() const override;
  std::string getSourceFileName() const override;
  uint32_t getStride() const override;
  uint32_t getSubTypeId() const override;
  std::string getSymbolsFileName() const override;
  uint32_t getSymIndexId() const override;
  uint32_t getTargetOffset() const override;
  uint32_t getTargetRelativeVirtualAddress() const override;
  uint64_t getTargetVirtualAddress() const override;
  uint32_t getTargetSection() const override;
  uint32_t getTextureSlot() const override;
  uint32_t getTimeStamp() const override;
  uint32_t getToken() const override;
  uint32_t getTypeId() const override;
  uint32_t getUavSlot() const override;
  std::string getUndecoratedName() const override;
  uint32_t getUnmodifiedTypeId() const override;
  uint32_t getUpperBoundId() const override;
  Variant getValue() const override;
  uint32_t getVirtualBaseDispIndex() const override;
  uint32_t getVirtualBaseOffset() const override;
  uint32_t getVirtualTableShapeId() const override;
  PDB_DataKind getDataKind() const override;
  PDB_SymType getSymTag() const override;
  PDB_UniqueId getGuid() const override;
  int32_t getOffset() const override;
  int32_t getThisAdjust() const override;
  int32_t getVirtualBasePointerOffset() const override;
  PDB_LocType getLocationType() const override;
  PDB_Machine getMachineType() const override;
  PDB_ThunkOrdinal getThunkOrdinal() const override;
  uint64_t getLength() const override;
  uint64_t getLiveRangeLength() const override;
  uint64_t getVirtualAddress() const override;
  PDB_UdtType getUdtKind() const override;
  bool hasConstructor() const override;
  bool hasCustomCallingConvention() const override;
  bool hasFarReturn() const override;
  bool isCode() const override;
  bool isCompilerGenerated() const override;
  bool isConstType() const override;
  bool isEditAndContinueEnabled() const override;
  bool isFunction() const override;
  bool getAddressTaken() const override;
  bool getNoStackOrdering() const override;
  bool hasAlloca() const override;
  bool hasAssignmentOperator() const override;
  bool hasCTypes() const override;
  bool hasCastOperator() const override;
  bool hasDebugInfo() const override;
  bool hasEH() const override;
  bool hasEHa() const override;
  bool hasInlAsm() const override;
  bool hasInlineAttribute() const override;
  bool hasInterruptReturn() const override;
  bool hasFramePointer() const override;
  bool hasLongJump() const override;
  bool hasManagedCode() const override;
  bool hasNestedTypes() const override;
  bool hasNoInlineAttribute() const override;
  bool hasNoReturnAttribute() const override;
  bool hasOptimizedCodeDebugInfo() const override;
  bool hasOverloadedOperator() const override;
  bool hasSEH() const override;
  bool hasSecurityChecks() const override;
  bool hasSetJump() const override;
  bool hasStrictGSCheck() const override;
  bool isAcceleratorGroupSharedLocal() const override;
  bool isAcceleratorPointerTagLiveRange() const override;
  bool isAcceleratorStubFunction() const override;
  bool isAggregated() const override;
  bool isIntroVirtualFunction() const override;
  bool isCVTCIL() const override;
  bool isConstructorVirtualBase() const override;
  bool isCxxReturnUdt() const override;
  bool isDataAligned() const override;
  bool isHLSLData() const override;
  bool isHotpatchable() const override;
  bool isIndirectVirtualBaseClass() const override;
  bool isInterfaceUdt() const override;
  bool isIntrinsic() const override;
  bool isLTCG() const override;
  bool isLocationControlFlowDependent() const override;
  bool isMSILNetmodule() const override;
  bool isMatrixRowMajor() const override;
  bool isManagedCode() const override;
  bool isMSILCode() const override;
  bool isMultipleInheritance() const override;
  bool isNaked() const override;
  bool isNested() const override;
  bool isOptimizedAway() const override;
  bool isPacked() const override;
  bool isPointerBasedOnSymbolValue() const override;
  bool isPointerToDataMember() const override;
  bool isPointerToMemberFunction() const override;
  bool isPureVirtual() const override;
  bool isRValueReference() const override;
  bool isRefUdt() const override;
  bool isReference() const override;
  bool isRestrictedType() const override;
  bool isReturnValue() const override;
  bool isSafeBuffers() const override;
  bool isScoped() const override;
  bool isSdl() const override;
  bool isSingleInheritance() const override;
  bool isSplitted() const override;
  bool isStatic() const override;
  bool hasPrivateSymbols() const override;
  bool isUnalignedType() const override;
  bool isUnreached() const override;
  bool isValueUdt() const override;
  bool isVirtual() const override;
  bool isVirtualBaseClass() const override;
  bool isVirtualInheritance() const override;
  bool isVolatileType() const override;
  bool wasInlined() const override;
  std::string getUnused() const override;

private:
  const DIASession &Session;
  CComPtr<IDiaSymbol> Symbol;
};
}

#endif
