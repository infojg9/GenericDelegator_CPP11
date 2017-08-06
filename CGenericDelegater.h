/**
 * Author: https://github.com/infojg9
 * MIT/BSD Redistributable License
 */

#pragma once

/// Use compiler flag for target specific selection: -DGENERIC_DELEGATE_ON
#ifdef GENERIC_DELEGATE_ON
// ----------------------------------------------------------------------------
// CGenericDelegater template
// ----------------------------------------------------------------------------
template<typename retType, typename... Params>
class CGenericDelegater {
  using pFnPtr = retType(*)(void* pfCallOrigin, Params...);

  // ------------------------------------------------------------------------
  // public delegator methods
  // ------------------------------------------------------------------------
public:

  CGenericDelegater(void* pfCallOrigin, pFnPtr callerFn)
    : m_fpCallPtr(pfCallOrigin)
    , m_fpCbkPtr(callerFn) {}

  template <typename Type, retType (Type::*TypeFn)(Params...)>
  static CGenericDelegater makeDelegation(Type* pfCallOrigin) {
    CGenericDelegater obDelegate(pfCallOrigin, &delegationImpl<Type, TypeFn>);
    return obDelegate;
  }

  retType operator()(Params... args) const {
    return (*m_fpCbkPtr)(m_fpCallPtr, args...);
  }

  bool operator==(CGenericDelegater const& other) const {
    return (m_fpCallPtr == other.m_fpCallPtr) && (m_fpCbkPtr == other.m_fpCbkPtr);
  }
  // ------------------------------------------------------------------------
  // private members and methods
  // ------------------------------------------------------------------------
private:

  template <typename Type, retType(Type::*TypeFn)(Params...)>
  static retType delegationImpl(void* pfCallOrigin, Params... args) {
    Type* p = static_cast<Type*>(pfCallOrigin);
    return (p->*TypeFn)(args...);
  }

  void*  m_fpCallPtr;
  pFnPtr m_fpCbkPtr;
}; // class CGenericDelegater

template<typename Type, typename retType, typename... Params>
struct DelegateData
{
  template<retType (Type::*TypeFn)(Params...)>
  static retType methodCaller(void* pfCallOrigin, Params... args)
  {
    return (static_cast<Type*>(pfCallOrigin)->*TypeFn)(args...);
  }

  template<retType (Type::*TypeFn)(Params...)>
  inline static CGenericDelegater<retType, Params...> makeAttach(Type* pfCallOrigin)
  {
    return CGenericDelegater<retType, Params...>
      (pfCallOrigin, &DelegateData::methodCaller<TypeFn>);
  }
};

/// Implicit delegation call: convention 2: short but complex: expansion
template<typename FnType, typename retType2, typename... Params2>
DelegateData<FnType, retType2, Params2...>
genDelegate(retType2 (FnType::*)(Params2...))
{
  return DelegateData<FnType, retType2, Params2...>();
}

/// "C" style Macro for External Header for application class usage:
/// convention 2: short but complex
#define GENERIC_DELEGATE(TypeFn, delegatedObj) (genDelegate(TypeFn).makeAttach<TypeFn>(delegatedObj))

#endif
