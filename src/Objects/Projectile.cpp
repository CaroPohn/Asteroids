#include "Projectile.h"


namespace Asteroids
{
    Projectile CreateProjectile(Vector2 position, Vector2 direction)
    {
        Projectile projectile;

        projectile.isActive = true;
        projectile.position = position;
        projectile.direction = direction;

        return projectile;
    }

    void ProjectileUpdate(Projectile& projectile)
    {
        if (!projectile.isActive)
            return;

        projectile.currentTime += GetFrameTime();

        if (projectile.currentTime > projectile.timeAlive)
        {
            projectile.isActive = false;
            return;
        }

        projectile.position.x += projectile.speed * projectile.direction.x * GetFrameTime();
        projectile.position.y += projectile.speed * projectile.direction.y * GetFrameTime();
    }

    void ProjectileDraw(Projectile& projectile)
    {
        if (projectile.isActive)
        {
            DrawCircle(static_cast<int>(projectile.position.x), static_cast<int>(projectile.position.y), projectile.radius, RED);
        }
    }
}
