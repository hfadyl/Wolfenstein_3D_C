/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfadyl <hfadyl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/12 12:49:33 by hfadyl            #+#    #+#             */
/*   Updated: 2020/11/20 17:19:20 by hfadyl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

t_pos	lastinter_h(void)
{
	t_pos	h;

	h.y = floor(t_player.pos.y / TILE_SIZE) * TILE_SIZE;
	h.y += (!t_ray.faceup) ? TILE_SIZE : 0;
	h.x = t_player.pos.x + ((h.y - t_player.pos.y) / tan(t_ray.ang * RAD));
	t_ray.ystep = TILE_SIZE;
	t_ray.ystep *= (t_ray.faceup) ? -1 : 1;
	t_ray.xstep = TILE_SIZE / tan(t_ray.ang * RAD);
	t_ray.xstep *= (t_ray.faceleft && t_ray.xstep > 0) ? -1 : 1;
	t_ray.xstep *= (!t_ray.faceleft && t_ray.xstep < 0) ? -1 : 1;
	while (t_map.len.width > (int)(h.x / TILE_SIZE)
		&& (int)(h.x / TILE_SIZE) > 0
		&& t_map.len.height > (int)(h.y / TILE_SIZE)
		&& (int)(h.y / TILE_SIZE) > 0
		&& !checkforwall(h, 1))
	{
		h.x += t_ray.xstep;
		h.y += t_ray.ystep;
	}
	return (h);
}

t_pos	lastinter_v(void)
{
	t_pos	v;

	v.x = floor(t_player.pos.x / TILE_SIZE) * TILE_SIZE;
	v.x += (!t_ray.faceleft) ? TILE_SIZE : 0;
	v.y = t_player.pos.y + ((v.x - t_player.pos.x) * tan(t_ray.ang * RAD));
	t_ray.xstep = TILE_SIZE;
	t_ray.xstep *= (t_ray.faceleft) ? -1 : 1;
	t_ray.ystep = TILE_SIZE * tan(t_ray.ang * RAD);
	t_ray.ystep *= (t_ray.faceup && t_ray.ystep > 0) ? -1 : 1;
	t_ray.ystep *= (!t_ray.faceup && t_ray.ystep < 0) ? -1 : 1;
	while (t_map.len.width > (int)(v.x / TILE_SIZE)
		&& (int)(v.x / TILE_SIZE) > 0
		&& t_map.len.height > (int)(v.y / TILE_SIZE)
		&& (int)(v.y / TILE_SIZE) > 0
		&& !checkforwall(v, 0))
	{
		v.x += t_ray.xstep;
		v.y += t_ray.ystep;
	}
	return (v);
}

float	get_dest(float angle)
{
	t_pos	h;
	t_pos	v;
	float	dsth;
	float	dstv;

	t_ray.ang = normalizeang(t_player.ang + angle);
	h = lastinter_h();
	v = lastinter_v();
	dsth = sqrt(pow((t_player.pos.x - h.x), 2) +
			pow((t_player.pos.y - h.y), 2));
	dstv = sqrt(pow((t_player.pos.x - v.x), 2) +
			pow((t_player.pos.y - v.y), 2));
	t_ray.horay = (dsth < dstv) ? 1 : 0;
	t_full.offset = (dsth < dstv) ? fmod(h.x, TILE_SIZE) : fmod(v.y, TILE_SIZE);
	return ((dsth < dstv) ? dsth : dstv);
}
