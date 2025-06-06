/// @dir
/// @brief @ref collisions-plugin plugin directory.

/// @file
/// @brief Plugin entry point.
/// @ingroup collisions-plugin

/// @dir ./shapes
/// @brief Collision shapes components directory.

/// @dir ./broad_phase
/// @brief Broad phase collision sub-plugin directory.

#pragma once

#include <cubos/engine/prelude.hpp>
#include <cubos/engine/transform/plugin.hpp>

namespace cubos::engine
{

    /// @defgroup collisions-plugin Collisions
    /// @ingroup engine
    /// @brief Adds collision detection to @b Cubos
    ///
    /// ## Components
    /// - @ref BoxCollisionShape - holds the box collision shape.
    /// - @ref CapsuleCollisionShape - holds the capsule collision shape.
    /// - @ref VoxelCollisionShape - holds the voxel collision shape.
    /// - @ref Collider - holds collider data.
    /// - @ref CollisionLayers - holds the collision layers where the collider appears in.
    /// - @ref CollisionMask - holds the mask of layers which the collider can collide with.
    ///
    /// ## Events
    /// - @ref CollisionEvent - (TODO) emitted when a collision occurs.
    /// - @ref TriggerEvent - (TODO) emitted when a trigger is entered or exited.
    ///
    /// ## Dependencies
    /// - @ref transform-plugin

    /// @brief Detects collisions and updates colliders.
    CUBOS_ENGINE_API extern Tag collisionsTag;

    /// @brief Plugin entry function.
    /// @param cubos @b Cubos main class.
    /// @ingroup collisions-plugin
    CUBOS_ENGINE_API void collisionsPlugin(Cubos& cubos);
} // namespace cubos::engine
