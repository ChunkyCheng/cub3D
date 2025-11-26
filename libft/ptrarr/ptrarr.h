/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ptrarr.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchuah <jchuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 15:44:32 by jchuah            #+#    #+#             */
/*   Updated: 2025/10/02 16:31:51 by jchuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PTRARR_H
# define PTRARR_H

# include <stdlib.h>

//do not use any of these functions without a wrapper as they are not type safe
size_t	ft_ptrarr_len(void *const *ptrarr);
void	**ft_ptrarr_dup(void *const *ptrarr);
void	**ft_ptrarr_join(void *const *ptrarr1, void *const *ptrarr2);

#endif
