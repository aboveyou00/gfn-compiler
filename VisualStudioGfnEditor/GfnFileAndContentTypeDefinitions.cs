using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.ComponentModel.Composition;
using Microsoft.VisualStudio.Text.Classification;
using Microsoft.VisualStudio.Utilities;

namespace VisualStudioGfnEditor
{
    /// <summary>
    /// File and content type definition exports
    /// </summary>
    internal class GfnFileAndContentTypeDefinitions
    {
        // This disables "The field is never used" compiler's warning. Justification: the field is used by MEF.
#pragma warning disable 169

        [Export(typeof(ContentTypeDefinition))]
        [Name("gfn")]
        [BaseDefinition("code")]
        internal static ContentTypeDefinition contentTypeDefinition;

        [Export(typeof(FileExtensionToContentTypeDefinition))]
        [FileExtension(".gfn")]
        [ContentType("gfn")]
        internal static FileExtensionToContentTypeDefinition fileExtensionToContentTypeDefinition;

#pragma warning restore 169
    }
}
