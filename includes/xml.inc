/**
 * The contents of this file are subject to the Mozilla Public License
 * Version 1.1 (the "License"); you may not use this file except in compliance
 * with the License. You may obtain a copy of the License at
 *
 * http://www.mozilla.org/MPL/
 *
 * Software distributed under the License is distributed on an "AS IS"
 * basis, WITHOUT WARRANTY OF ANY KIND, either express or implied.
 * See the License for the specific language governing rights and
 * limitations under the License.
 *
 * The Original Code is SA:MP XML plugin.
 * The Initial Developer of the Original Code is Sergey "Zeex" Zolotaryov.
 *
 * All Rights Reserved.
 */

enum e_XML_NODE_TYPE {
	e_XML_NODE_DOCUMENT,
	e_XML_NODE_ELEMENT,
	e_XML_NODE_COMMENT,
	e_XML_NODE_UNKNOWN,
	e_XML_NODE_TEXT,
	e_XML_NODE_DECLARATION,
    e_XML_NODE_TYPECOUNT
};

/**
 * Creates a new document.
 *
 * @param filename The file name that will be used on saving.
 * @param version  The XML version (optional, defaults to "1.0").
 * @param encoding Character encoding which appears in XML declaration.
 *
 * @returns Handle to document tree root node.
 */
native XMLNode:XML_CreateDocument(const filename[], const version[] = "1.0", const encoding[] = "ISO-8859-1");

/**
 * Loads a document from a file.
 *
 * @param filename Path to the file
 *
 * @returns Handle to the document tree root node.
 *
 * @see XML_SaveDocument
 * @see XML_UnloadDocument
 */
native XMLNode:XML_LoadDocument(const filename[]);

/**
 * Saves a document to a file.
 *
 * @param doc      Handle to document root.
 * @param filename The file name (optional).
 *
 * @returns True on success, or false if failed.
 *
 * @see XML_LoadDocument
 * @see XML_UnloadDocument
 */
native bool:XML_SaveDocument(XMLNode:doc, const filename[] = "");

/**
 * Fully destroys a document (i.e. including all of its nodes) and frees memory.
 *
 * @param doc The document to be unloaded.
 *
 * @see XML_LoadDocument
 * @see XML_SaveDocument
 */
native XML_UnloadDocument(XMLNode:doc);

/**
 * Creates a new node and optionally makes it to be a child of another one.
 *
 * @param parent Parent node, use 0 to specify no parent.
 * @param value  Node value. Defined as:
 *                 Document: filename of the xml file
 *                 Element:  name of the element
 *                 Comment:  the comment text
 *                 Unknown:  the tag contents
 *                 Text:     the text string
 * @param type   Node type, can be either ELEMENT, COMMENT or TEXT.
 *
 * @returns Handle to the newely created node or 0 if failed.
 *
 * @see XML_DestroyNode
 */
native XMLNode:XML_CreateNode(XMLNode:parent, const value[], e_XML_NODE_TYPE:type = e_XML_NODE_ELEMENT);

/**
 * Deletes a specific child of a node and replaces it with a new one.
 *
 * @param parent   The parent node.
 * @param oldChild The child to be replaced.
 * @param newChild The new child.
 *
 * @returns True on success, or false if failed.
 *
 * @see XML_ReplaceChild
 */
//native bool:XML_ReplaceChild(XMLNode:parent, XMLNode:oldChild, XMLNode:newChild);

/**
 * Removes a specific child of a node and deletes it from memory.
 *
 * @param parent The parent node.
 * @param child  The child to be removed.
 *
 * @returns True on success, or false if failed.
 *
 * @see XML_ReplaceChild
 */
native bool:XML_RemoveChild(XMLNode:parent, XMLNode:child);

/**
 * Deletes selected node from memory.
 *
 * @param node The node to be destroyed.
 *
 * @see XML_CreateNode
 */
native XML_DestroyNode(XMLNode:node);

/**
 * Finds first child of a selected node by its value.
 *
 * @param node  The node to get the child of.
 * @param value The value to be searched for (optional).
 *
 * @returns Child node hanle or 0 if not found.
 *
 * @see XML_GetLastChild
 */
native XMLNode:XML_GetFirstChild(XMLNode:node, const value[] = "");

/**
 * Finds first child of a selected node by its value.
 *
 * @param node  The node to get the child of.
 * @param value The value to be searched for (optional).
 *
 * @returns Child node hanle or 0 if not found.
 *
 * @see XML_GetFirstChild
 */
native XMLNode:XML_GetLastChild(XMLNode:node, const value[] = "");

/**
 * Finds next sibling of a selected node by its value.
 *
 * @param node  The node to find sibling of.
 * @param value The value to be searched for (optional).
 *
 * @returns Sibling handle of 0 if not found.
 *
 * @see XML_GetPreviousSibling
 */
native XMLNode:XML_GetNextSibling(XMLNode:node, const value[] = "");

/**
 * Finds previous sibling of a selected node by its value.
 *
 * @param node  The node to find sibling of.
 * @param value The value to be searched for (optional).
 *
 * @returns Sibling handle of 0 if not found.
 *
 * @see XML_GetNextSibling
 */
native XMLNode:XML_GetPreviousSibling(XMLNode:node, const value[] = "");

/** Returns node parent.
 *
 * @param node The node.
 *
 * @returns Handle to the parent node or 0 if it has no parent.
 */
native XMLNode:XML_GetParent(XMLNode:node);

/**
 * Gets node value.
 *
 * @param node   The node to get value of.
 * @param value  An array which will hold the value.
 * @param maxlen Maximum value length.
 *
 * @see XML_SetValue
 */
native XML_GetValue(XMLNode:node, value[], maxlen = sizeof(value));

/**
 * Sets node value.
 *
 * @param node The node to set value of.
 * @param value The value to be set. Defined as:
 *                Document: filename of the xml file
 *                Element:  name of the element
 *                Comment:  the comment text
 *                Unknown:  the tag contents
 *                Text:     the text string
 *
 * @see XML_GetValue
 */
native XML_SetValue(XMLNode:node, const value[]);

/**
 * Gets element attribute value.
 *
 * @param element The node to get attribute of (it should be an element node).
 * @param name    Attribute name.
 * @param value   Attribute value will be copied here.
 * @param maxlen  Maximum value length.
 *
 * @see XML_SetAttribute
 * @see XML_RemoveAttribute
 */
native XML_GetAttribute(XMLNode:element, const name[], value[], maxlen = sizeof(value));

/**
 * Sets element attribute value.
 *
 * @param element The node to set attribute of (it should be an element node).
 * @param name    Attribute name.
 * @param value   Attribute value.
 *
 * @see XML_GetAttribute
 * @see XML_RemoveAttribute
 */
native XML_SetAttribute(XMLNode:element, const name[], const value[]);

/**
 * Removes selected attribute of an element.
 *
 * @param element The node (should be an element node).
 * @param name    Attribute name.
 *
 * @see XML_GetAttribute
 * @see XML_SetAttribute
 */
native XML_RemoveAttribute(XMLNode:element, const name[]);

/**
 * Gets node type.
 *
 * @param node The node.
 *
 * @returns The type of the specified node.
 */
native e_XML_NODE_TYPE:XML_GetNodeType(XMLNode:node);

/**
 * Computes an integer XPath expression.
 *
 * @param root Handle to a source tree root.
 * @param xpath The XPath expression.
 *
 * @returns Expression value.
 */
native XML_GetXPathInt(XMLNode:root, const xpath[]);

/**
 * Computes a boolean XPath expression.
 *
 * @param root Handle to a source tree root.
 * @param xpath The XPath expression.
 *
 * @returns Expression value.
 */
native bool:XML_GetXPathBool(XMLNode:root, const xpath[]);

/**
 * Computes a float XPath expression.
 *
 * @param root Handle to a source tree root.
 * @param xpath The XPath expression.
 *
 * @returns Expression value.
 */
native Float:XML_GetXPathFloat(XMLNode:root, const xpath[]);

/**
 * Computes a string XPath expression.
 *
 * @param root Handle to a source tree root.
 * @param xpath The XPath expression.
 *
 * @returns Expression value.
 */
native XML_GetXPathString(XMLNode:root, const xpath[], result[], maxlen = sizeof(result));

/**
 * Computes a node XPath expression.
 *
 * @param root Handle to a source tree root.
 * @param xpath The XPath expression.
 *
 * @returns Expression value.
 */
native XMLNode:XML_GetXPathNode(XMLNode:root, const xpath[]);

/**
 * Computes an attribute XPath expression.
 *
 * @param root Handle to a source tree root.
 * @param xpath The XPath expression.
 *
 * @returns Expression value.
 */
native XMLAttr:XML_GetXPathAttribute(XMLNode:root, const xpath[]);
