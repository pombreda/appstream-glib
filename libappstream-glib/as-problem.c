/* -*- Mode: C; tab-width: 8; indent-tabs-mode: t; c-basic-offset: 8 -*-
 *
 * Copyright (C) 2014 Richard Hughes <richard@hughsie.com>
 *
 * Licensed under the GNU Lesser General Public License Version 2.1
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301 USA
 */

/**
 * SECTION:as-problem
 * @short_description: Object representing a problem with an application
 * @include: appstream-glib.h
 * @stability: Stable
 *
 * Problems have a unlocalized message and also contain a line number and kind.
 *
 * See also: #AsApp
 */

#include "config.h"

#include "as-problem.h"

typedef struct _AsProblemPrivate	AsProblemPrivate;
struct _AsProblemPrivate
{
	AsProblemKind		 kind;
	gchar			*message;
	guint			 line_number;
};

G_DEFINE_TYPE_WITH_PRIVATE (AsProblem, as_problem, G_TYPE_OBJECT)

#define GET_PRIVATE(o) (as_problem_get_instance_private (o))

/**
 * as_problem_finalize:
 **/
static void
as_problem_finalize (GObject *object)
{
	AsProblem *problem = AS_PROBLEM (object);
	AsProblemPrivate *priv = GET_PRIVATE (problem);

	g_free (priv->message);

	G_OBJECT_CLASS (as_problem_parent_class)->finalize (object);
}

/**
 * as_problem_init:
 **/
static void
as_problem_init (AsProblem *problem)
{
	AsProblemPrivate *priv = GET_PRIVATE (problem);
	priv->kind = AS_PROBLEM_KIND_UNKNOWN;
	priv->line_number = 0;
}

/**
 * as_problem_class_init:
 **/
static void
as_problem_class_init (AsProblemClass *klass)
{
	GObjectClass *object_class = G_OBJECT_CLASS (klass);
	object_class->finalize = as_problem_finalize;
}

/**
 * as_problem_kind_to_string:
 * @kind: the #AsProblemKind.
 *
 * Converts the enumerated value to an text representation.
 *
 * Returns: string version of @kind
 *
 * Since: 0.1.4
 **/
const gchar *
as_problem_kind_to_string (AsProblemKind kind)
{
	if (kind == AS_PROBLEM_KIND_TAG_DUPLICATED)
		return "tag-duplicated";
	if (kind == AS_PROBLEM_KIND_TAG_MISSING)
		return "tag-missing";
	if (kind == AS_PROBLEM_KIND_TAG_INVALID)
		return "tag-invalid";
	if (kind == AS_PROBLEM_KIND_ATTRIBUTE_MISSING)
		return "attribute-missing";
	if (kind == AS_PROBLEM_KIND_ATTRIBUTE_INVALID)
		return "attribute-invalid";
	if (kind == AS_PROBLEM_KIND_MARKUP_INVALID)
		return "markup-invalid";
	if (kind == AS_PROBLEM_KIND_STYLE_INCORRECT)
		return "style-invalid";
	if (kind == AS_PROBLEM_KIND_TRANSLATIONS_REQUIRED)
		return "translations-required";
	if (kind == AS_PROBLEM_KIND_DUPLICATE_DATA)
		return "duplicate-data";
	if (kind == AS_PROBLEM_KIND_VALUE_MISSING)
		return "value-missing";
	if (kind == AS_PROBLEM_KIND_FILE_INVALID)
		return "file-invalid";
	if (kind == AS_PROBLEM_KIND_ASPECT_RATIO_INCORRECT)
		return "aspect-ratio-invalid";
	if (kind == AS_PROBLEM_KIND_RESOLUTION_INCORRECT)
		return "resolution-invalid";
	if (kind == AS_PROBLEM_KIND_URL_NOT_FOUND)
		return "url-not-found";
	return NULL;
}

/**
 * as_problem_get_kind:
 * @problem: a #AsProblem instance.
 *
 * Gets the problem kind.
 *
 * Returns: a #AsProblemKind, e.g. %AS_PROBLEM_KIND_TAG_MISSING
 *
 * Since: 0.1.4
 **/
AsProblemKind
as_problem_get_kind (AsProblem *problem)
{
	AsProblemPrivate *priv = GET_PRIVATE (problem);
	return priv->kind;
}

/**
 * as_problem_get_line_number:
 * @problem: a #AsProblem instance.
 *
 * Gets the line number of the problem if known.
 *
 * Returns: a line number, where 0 is unknown
 *
 * Since: 0.1.4
 **/
guint
as_problem_get_line_number (AsProblem *problem)
{
	AsProblemPrivate *priv = GET_PRIVATE (problem);
	return priv->line_number;
}

/**
 * as_problem_get_message:
 * @problem: a #AsProblem instance.
 *
 * Gets the specific message for the problem.
 *
 * Returns: the message
 *
 * Since: 0.1.4
 **/
const gchar *
as_problem_get_message (AsProblem *problem)
{
	AsProblemPrivate *priv = GET_PRIVATE (problem);
	return priv->message;
}

/**
 * as_problem_set_kind:
 * @problem: a #AsProblem instance.
 * @kind: the #AsProblemKind.
 *
 * Sets the problem kind.
 *
 * Since: 0.1.4
 **/
void
as_problem_set_kind (AsProblem *problem, AsProblemKind kind)
{
	AsProblemPrivate *priv = GET_PRIVATE (problem);
	priv->kind = kind;
}

/**
 * as_problem_set_line_number:
 * @problem: a #AsProblem instance.
 * @line_number: a #guint instance.
 *
 * Adds an line_number to the problem.
 *
 * Since: 0.1.4
 **/
void
as_problem_set_line_number (AsProblem *problem, guint line_number)
{
	AsProblemPrivate *priv = GET_PRIVATE (problem);
	priv->line_number = line_number;
}

/**
 * as_problem_set_message:
 * @problem: a #AsProblem instance.
 * @message: the message text.
 *
 * Sets a message on the problem.
 *
 * Since: 0.1.4
 **/
void
as_problem_set_message (AsProblem *problem, const gchar *message)
{
	AsProblemPrivate *priv = GET_PRIVATE (problem);
	g_free (priv->message);
	priv->message = g_strdup (message);
}

/**
 * as_problem_new:
 *
 * Creates a new #AsProblem.
 *
 * Returns: (transfer full): a #AsProblem
 *
 * Since: 0.1.4
 **/
AsProblem *
as_problem_new (void)
{
	AsProblem *problem;
	problem = g_object_new (AS_TYPE_PROBLEM, NULL);
	return AS_PROBLEM (problem);
}
