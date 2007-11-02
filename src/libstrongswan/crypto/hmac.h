/**
 * @file hmac.h
 * 
 * @brief Interface of hmac_t.
 */

/*
 * Copyright (C) 2005-2006 Martin Willi
 * Copyright (C) 2005 Jan Hutter
 * Hochschule fuer Technik Rapperswil
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.  See <http://www.fsf.org/copyleft/gpl.txt>.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 */

#ifndef HMAC_H_
#define HMAC_H_

typedef struct hmac_t hmac_t;

#include <crypto/hashers/hasher.h>

/**
 * @brief Message authentication using hash functions.
 *
 * This class implements the message authenticaion algorithm
 * described in RFC2104. It uses a hash function, wich must
 * be implemented as a hasher_t class.
 *
 * See http://www.faqs.org/rfcs/rfc2104.html for RFC.
 * @see 	
 * 			- hasher_t
 * 			- prf_hmac_t
 *
 * @b Constructors:
 *  - hmac_create()
 *
 * @ingroup crypto
 */
struct hmac_t {
	/**
	 * @brief Generate message authentication code.
	 * 
	 * If buffer is NULL, no result is given back. A next call will
	 * append the data to already supplied data. If buffer is not NULL, 
	 * the mac of all apended data is calculated, returned and the
	 * state of the hmac_t is reseted.
	 * 
	 * @param this			calling object
	 * @param data			chunk of data to authenticate
	 * @param[out] buffer	pointer where the generated bytes will be written
	 */
	void (*get_mac) (hmac_t *this, chunk_t data, u_int8_t *buffer);
	
	/**
	 * @brief Generates message authentication code and 
	 * allocate space for them.
	 * 
	 * If chunk is NULL, no result is given back. A next call will
	 * append the data to already supplied. If chunk is not NULL, 
	 * the mac of all apended data is calculated, returned and the
	 * state of the hmac_t reset;
	 * 
	 * @param this			calling object
	 * @param data			chunk of data to authenticate
	 * @param[out] chunk	chunk which will hold generated bytes
	 */
	void (*allocate_mac) (hmac_t *this, chunk_t data, chunk_t *chunk);
	
	/**
	 * @brief Get the block size of this hmac_t object.
	 * 
	 * @param this			calling object
	 * @return				block size in bytes
	 */
	size_t (*get_block_size) (hmac_t *this);	
	
	/**
	 * @brief Set the key for this hmac_t object.
	 * 
	 * Any key length is accepted.
	 * 
	 * @param this			calling object
	 * @param key			key to set
	 */
	void (*set_key) (hmac_t *this, chunk_t key);
	
	/**
	 * @brief Destroys a hmac_t object.
	 *
	 * @param this 			calling object
	 */
	void (*destroy) (hmac_t *this);
};

/**
 * @brief Creates a new hmac_t object.
 * 
 * Creates a hasher_t object internally.
 * 
 * @param hash_algorithm		hash algorithm to use
 * @return
 *								- hmac_t object
 *								- NULL if hash algorithm is not supported
 * 
 * @ingroup transforms
 */
hmac_t *hmac_create(hash_algorithm_t hash_algorithm);

#endif /*HMAC_H_*/