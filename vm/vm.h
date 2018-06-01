/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astadnik <astadnik@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/31 18:15:23 by astadnik          #+#    #+#             */
/*   Updated: 2018/05/31 18:50:15 by astadnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
#define VM_H

typedef struct
{
	unsigned	pc;
	unsigned	registers[16];
	char		carry;

}				t_carriage;

typedef struct
{
	unsigned char	arena[4096];
	t_list		*carriages;

}				t_info;

#endif
