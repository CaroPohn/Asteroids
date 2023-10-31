#include "Projectile.h"

#include <cmath>

namespace Asteroids
{
    Projectile CreateProjectile(Vector2 position, float rotation)
    {
        Projectile projectile;

        projectile.isActive = true;
        projectile.position = position;
        projectile.rotation = rotation;
        projectile.creationTime = static_cast<float>(GetTime());

        return projectile;
    }

    void ProjectileUpdate(Projectile& projectile)
    {
        if (!projectile.isActive)
            return;

        if (GetTime() > projectile.creationTime + PROJECTILE_LIFE)
        {
            projectile.isActive = false;
            return;
        }

        projectile.position.x = PROJECTILE_SPEED * cos(projectile.rotation) * GetFrameTime();
        projectile.position.y = PROJECTILE_SPEED * sin(projectile.rotation) * GetFrameTime();
    }

    void ProjectileDraw(Projectile projectile)
    {
        Rectangle rect = { projectile.position.x, projectile.position.y, PROJECTILE_WIDTH, PROJECTILE_HEIGHT };
        Vector2 origin = { rect.width / 2, rect.height / 2 };
        DrawRectanglePro(rect, origin, projectile.rotation, RED);
    }

}
