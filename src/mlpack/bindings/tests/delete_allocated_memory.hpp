/**
 * @file delete_allocated_memory.hpp
 * @author Ryan Curtin
 *
 * If any memory has been allocated by the parameter, delete it.
 */
#ifndef MLPACK_BINDINGS_CLI_DELETE_ALLOCATED_MEMORY_HPP
#define MLPACK_BINDINGS_CLI_DELETE_ALLOCATED_MEMORY_HPP

#include <mlpack/core/util/param_data.hpp>

namespace mlpack {
namespace bindings {
namespace tests {

template<typename T>
void DeleteAllocatedMemoryImpl(
    const util::ParamData& /* d */,
    const typename boost::disable_if<data::HasSerialize<T>>::type* = 0,
    const typename boost::disable_if<arma::is_arma_type<T>>::type* = 0)
{
  // Do nothing.
}

template<typename T>
void DeleteAllocatedMemoryImpl(
    const util::ParamData& /* d */,
    const typename boost::enable_if<arma::is_arma_type<T>>::type* = 0)
{
  // Do nothing.
}

template<typename T>
void DeleteAllocatedMemoryImpl(
    const util::ParamData& d,
    const typename boost::disable_if<arma::is_arma_type<T>>::type* = 0,
    const typename boost::enable_if<data::HasSerialize<T>>::type* = 0)
{
  // Delete the allocated memory (hopefully we actually own it).
  delete *boost::any_cast<T*>(&d.value);
}

template<typename T>
void DeleteAllocatedMemory(
    const util::ParamData& d,
    const void* /* input */,
    void* /* output */)
{
  DeleteAllocatedMemoryImpl<typename std::remove_pointer<T>::type>(d);
}

} // namespace cli
} // namespace bindings
} // namespace mlpack

#endif
