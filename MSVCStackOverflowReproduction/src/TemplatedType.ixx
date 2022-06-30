module;
#include <cstdint>
#include "EnumTypes.h"  // <- Comment out this #include and remove the '/' characters preceding "export import "EnumTypes.h"" to make the project build.

export module TemplatedType;
// export import "EnumTypes.h";

namespace NS
{
	template <StorageTypeID StorageType>
	struct StorageTypeInfo
	{
		static_assert(sizeof(StorageType) != sizeof(StorageType));
	};

	template <>
	struct StorageTypeInfo<StorageTypeID::INT_32>
	{
		using StoredType = std::int32_t;

		__forceinline static constexpr void ModifyCollection(StorageCollection& collection, const StoredType value)
		{
			collection.TypeID = StorageTypeID::INT_32;
			collection.Int32 = (value + 1);
		}
	};

	template <>
	struct StorageTypeInfo<StorageTypeID::UINT_32>
	{
		using StoredType = std::uint32_t;

		__forceinline static constexpr void ModifyCollection(StorageCollection& collection, const StoredType value)
		{
			collection.TypeID = StorageTypeID::UINT_32;
			collection.UInt32 = (value - 1);
		}
	};

	template <>
	struct StorageTypeInfo<StorageTypeID::FLOAT>
	{
		using StoredType = float;

		__forceinline static constexpr void ModifyCollection(StorageCollection& collection, const StoredType value)
		{
			collection.TypeID = StorageTypeID::FLOAT;
			collection.Float = (value * 2.0f);
		}
	};

	template <>
	struct StorageTypeInfo<StorageTypeID::DOUBLE>
	{
		using StoredType = double;

		__forceinline static constexpr void ModifyCollection(StorageCollection& collection, const StoredType value)
		{
			collection.TypeID = StorageTypeID::DOUBLE;
			collection.Double = (value / 2.0f);
		}
	};

	template <StorageTypeID StorageType>
	class TemplatedType;
}

export namespace NS
{
	template <StorageTypeID StorageType>
	class TemplatedType
	{
	private:
		using StoredType = typename StorageTypeInfo<StorageType>::StoredType;

	public:
		TemplatedType() = default;
		explicit TemplatedType(const StoredType value);

		TemplatedType(const TemplatedType& rhs) = default;
		TemplatedType& operator=(const TemplatedType& rhs) = default;

		TemplatedType(TemplatedType&& rhs) noexcept = default;
		TemplatedType& operator=(TemplatedType&& rhs) noexcept = default;

		StorageCollection GetStorageCollection() const;

	private:
		StoredType mValue;
	};
}

// ------------------------------------------------------------------------------------------------------------------------

namespace NS
{
	template <StorageTypeID StorageType>
	TemplatedType<StorageType>::TemplatedType(const StoredType value) :
		mValue(value)
	{}

	template <StorageTypeID StorageType>
	StorageCollection TemplatedType<StorageType>::GetStorageCollection() const
	{
		StorageCollection collection{};
		StorageTypeInfo<StorageType>::ModifyCollection(collection, mValue);
		
		return collection;
	}
}

export namespace NS
{
	using Int32TemplatedType = TemplatedType<StorageTypeID::INT_32>;
	using UInt32TemplatedType = TemplatedType<StorageTypeID::UINT_32>;
	using FloatTemplatedType = TemplatedType<StorageTypeID::FLOAT>;
	using DoubleTemplatedType = TemplatedType<StorageTypeID::DOUBLE>;
}