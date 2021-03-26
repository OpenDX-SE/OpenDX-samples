/*
 * Automatically generated on "/tmp/add2invalid.mb" by DX Module Builder
 */

#include "dx/dx.h"

static Error traverse(Object *, Object *);
static Error doLeaf(Object *, Object *);

/*
 * Declare the interface routine.
 */
int
Add2Invalid_worker(
    int, float *,
    int, float *,
    int, float *);

Error
m_Add2Invalid(Object *in, Object *out)
{
  int i;

  /*
   * Initialize all outputs to NULL
   */
  out[0] = NULL;

  /*
   * Error checks: required inputs are verified.
   */

  /* Parameter "field1" is required. */
  if (in[0] == NULL)
  {
    DXSetError(ERROR_MISSING_DATA, "\"field1\" must be specified");
    return ERROR;
  }

  /* Parameter "field2" is required. */
  if (in[1] == NULL)
  {
    DXSetError(ERROR_MISSING_DATA, "\"field2\" must be specified");
    return ERROR;
  }


  /*
   * Since output "result" is structure Field/Group, it initially
   * is a copy of input "field1".
   */
  out[0] = DXCopy(in[0], COPY_STRUCTURE);
  if (! out[0])
    goto error;

  /*
   * If in[0] was an array, then no copy is actually made - Copy 
   * returns a pointer to the input object.  Since this can't be written to
   * we postpone explicitly copying it until the leaf level, when we'll need
   * to be creating writable arrays anyway.
   */
  if (out[0] == in[0])
    out[0] = NULL;

  /*
   * Call the hierarchical object traversal routine
   */
  if (!traverse(in, out))
    goto error;

  return OK;

error:
  /*
   * On error, any successfully-created outputs are deleted.
   */
  for (i = 0; i < 1; i++)
  {
    if (in[i] != out[i])
      DXDelete(out[i]);
    out[i] = NULL;
  }
  return ERROR;
}


static Error
traverse(Object *in, Object *out)
{
  switch(DXGetObjectClass(in[0]))
  {
    case CLASS_FIELD:
    case CLASS_ARRAY:
      /*
       * If we have made it to the leaf level, call the leaf handler.
       */
      if (! doLeaf(in, out))
  	     return ERROR;

      return OK;

    case CLASS_GROUP:
    {
      int   i, j;
      int   memknt;
      Class groupClass  = DXGetGroupClass((Group)in[0]);

      DXGetMemberCount((Group)in[0], &memknt);

      /*
       * All inputs that are not NULL and are type Field/Group must
       * match the structure of input[0].  Verify that this is so.
       */
       if (in[1] &&
            (DXGetObjectClass(in[1]) != CLASS_GROUP ||
             DXGetGroupClass((Group)in[1])  != groupClass  ||
             !DXGetMemberCount((Group)in[1], &i) || i != memknt))
	      {
  		DXSetError(ERROR_DATA_INVALID,
	            "structure of \"field2\" doesn't match that of \"field1\"");
  	         return ERROR;
         }

       /*
        * Create new in and out lists for each child
        * of the first input. 
        */
        for (i = 0; i < memknt; i++)
        {
          Object new_in[2], new_out[1];

         /*
          * For all inputs that are Values, pass them to 
          * child object list.  For all that are Field/Group, get 
          * the appropriate decendent and place it into the
          * child input object list.
          */

          /* input "field1" is Field/Group */
          if (in[0])
            new_in[0] = DXGetEnumeratedMember((Group)in[0], i, NULL);
          else
            new_in[0] = NULL;

          /* input "field2" is Field/Group */
          if (in[1])
            new_in[1] = DXGetEnumeratedMember((Group)in[1], i, NULL);
          else
            new_in[1] = NULL;

         /*
          * For all outputs that are Values, pass them to 
          * child object list.  For all that are Field/Group,  get
          * the appropriate decendent and place it into the
          * child output object list.  Note that none should
          * be NULL (unlike inputs, which can default).
          */

          /* output "result" is Field/Group */
          new_out[0] = DXGetEnumeratedMember((Group)out[0], i, NULL);

          if (! traverse(new_in, new_out))
            return ERROR;

         /*
          * Now for each output that is not a Value, replace
          * the updated child into the object in the parent.
          */

          /* output "result" is Field/Group */
          DXSetEnumeratedMember((Group)out[0], i, new_out[0]);

        }
      return OK;
    }

    case CLASS_XFORM:
    {
      int    i, j;
      Object new_in[2], new_out[1];

      /*
       * All inputs that are not NULL and are type Field/Group must
       * match the structure of input[0].  Verify that this is so.
       */
      if (in[1] && DXGetObjectClass(in[1]) != CLASS_XFORM)
      {
        DXSetError(ERROR_DATA_INVALID,
	            "structure of \"field2\" doesn't match that of \"field1\"");
        return ERROR;
      }

      /*
       * Create new in and out lists for the decendent of the
       * first input.  For inputs and outputs that are Values
       * copy them into the new in and out lists.  Otherwise
       * get the corresponding decendents.
       */

      /* input "field1" is Field/Group */
      if (in[0])
        DXGetXformInfo((Xform)in[0], &new_in[0], NULL);
      else
        new_in[0] = NULL;

      /* input "field2" is Field/Group */
      if (in[1])
        DXGetXformInfo((Xform)in[1], &new_in[1], NULL);
      else
        new_in[1] = NULL;

      /*
       * For all outputs that are Values, copy them to 
       * child object list.  For all that are Field/Group,  get
       * the appropriate decendent and place it into the
       * child output object list.  Note that none should
       * be NULL (unlike inputs, which can default).
       */

      /* output "result" is Field/Group */
      DXGetXformInfo((Xform)out[0], &new_out[0], NULL);

      if (! traverse(new_in, new_out))
        return ERROR;

      /*
       * Now for each output that is not a Value replace
       * the updated child into the object in the parent.
       */

      /* output "result" is Field/Group */
      DXSetXformObject((Xform)out[0], new_out[0]);

      return OK;
    }

    case CLASS_SCREEN:
    {
      int    i, j;
      Object new_in[2], new_out[1];

      /*
       * All inputs that are not NULL and are type Field/Group must
       * match the structure of input[0].  Verify that this is so.
       */

       if (in[1] && DXGetObjectClass(in[1]) != CLASS_SCREEN)
       {
           DXSetError(ERROR_DATA_INVALID,
	            "structure of \"field2\" doesn't match that of \"field1\"");
           return ERROR;
       }

      /*
       * Create new in and out lists for the decendent of the
       * first input.  For inputs and outputs that are Values
       * copy them into the new in and out lists.  Otherwise
       * get the corresponding decendents.
       */

      /* input "field1" is Field/Group */
      if (in[0])
        DXGetScreenInfo((Screen)in[0], &new_in[0], NULL, NULL);
      else
        new_in[0] = NULL;

      /* input "field2" is Field/Group */
      if (in[1])
        DXGetScreenInfo((Screen)in[1], &new_in[1], NULL, NULL);
      else
        new_in[1] = NULL;


      /*
       * For all outputs that are Values, copy them to 
       * child object list.  For all that are Field/Group,  get
       * the appropriate decendent and place it into the
       * child output object list.  Note that none should
       * be NULL (unlike inputs, which can default).
       */

       /* output "result" is Field/Group */
       DXGetScreenInfo((Screen)out[0], &new_out[0], NULL, NULL);

       if (! traverse(new_in, new_out))
         return ERROR;

      /*
       * Now for each output that is not a Value, replace
       * the updated child into the object in the parent.
       */

      /* output "result" is Field/Group */
       DXSetScreenObject((Screen)out[0], new_out[0]);

       return OK;
     }

     case CLASS_CLIPPED:
     {
       int    i, j;
       Object new_in[2], new_out[1];

      /*
       * All inputs that are not NULL and are type Field/Group must
       * match the structure of input[0].  Verify that this is so.
       */

       if (in[1] && DXGetObjectClass(in[1]) != CLASS_CLIPPED)
       {
           DXSetError(ERROR_DATA_INVALID,
               "mismatching Field/Group objects");
           return ERROR;
       }

       /* input "field1" is Field/Group */
       if (in[0])
         DXGetClippedInfo((Clipped)in[0], &new_in[0], NULL);
       else
         new_in[0] = NULL;

       /* input "field2" is Field/Group */
       if (in[1])
         DXGetClippedInfo((Clipped)in[1], &new_in[1], NULL);
       else
         new_in[1] = NULL;


      /*
       * For all outputs that are Values, copy them to 
       * child object list.  For all that are Field/Group,  get
       * the appropriate decendent and place it into the
       * child output object list.  Note that none should
       * be NULL (unlike inputs, which can default).
       */

       /* output "result" is Field/Group */
       DXGetClippedInfo((Clipped)out[0], &new_out[0], NULL);

       if (! traverse(new_in, new_out))
         return ERROR;

      /*
       * Now for each output that is not a Value, replace
       * the updated child into the object in the parent.
       */

       /* output "result" is Field/Group */
       DXSetClippedObjects((Clipped)out[0], new_out[0], NULL);

       return OK;
     }

     default:
     {
       DXSetError(ERROR_BAD_CLASS, "encountered in object traversal");
       return ERROR;
     }
  }
}

static int
doLeaf(Object *in, Object *out)
{
  int i, result=0;
  Array array;
  Field field;
  Pointer *in_data[2], *out_data[1];
  int in_knt[2], out_knt[1];
  Type type;
  Category category;
  int rank, shape;
  Object attr, src_dependency_attr = NULL;
  char *src_dependency = NULL;
  int p_knt = -1;
  int c_knt = -1;
  InvalidComponentHandle inv_handle1, inv_handle2;
  float *out_ptr, *in1_ptr, *in2_ptr;



  if (DXGetObjectClass(in[0]) == CLASS_FIELD)
  {

    field = (Field)in[0];

    if (DXEmptyField(field))
      return OK;

    /* 
     * Determine the dependency of the source object's data
     * component.
     */
    src_dependency_attr = DXGetComponentAttribute(field, "data", "dep");
    if (! src_dependency_attr)
    {
      DXSetError(ERROR_MISSING_DATA, "\"field1\" data component is missing a dependency attribute");
      goto error;
    }

    if (DXGetObjectClass(src_dependency_attr) != CLASS_STRING)
    {
      DXSetError(ERROR_BAD_CLASS, "\"field1\" dependency attribute");
      goto error;
    }

    src_dependency = DXGetString((String)src_dependency_attr);

    array = (Array)DXGetComponentValue(field, "positions");
    if (! array)
    {
      DXSetError(ERROR_BAD_CLASS, "\"field1\" contains no positions component");
      goto error;
    }

    DXGetArrayInfo(array, &p_knt, NULL, NULL, NULL, NULL);
 }
  /*
   * If the input argument is not NULL then we get the 
   * data array: either the object itself, if its an 
   * array, or the data component if the argument is a field
   */
  if (! in[0])
  {
    array = NULL;
    in_data[0] = NULL;
    in_knt[0] = 0;
  }
  else
  {
    if (DXGetObjectClass(in[0]) == CLASS_ARRAY)
    {
      array = (Array)in[0];
    }
    else
    {
      if (DXGetObjectClass(in[0]) != CLASS_FIELD)
      {
        DXSetError(ERROR_BAD_CLASS, "\"field1\" should be a field");
        goto error;
      }

      array = (Array)DXGetComponentValue((Field)in[0], "data");
      if (! array)
      {
        DXSetError(ERROR_MISSING_DATA, "\"field1\" has no data component");
        goto error;
      }

      if (DXGetObjectClass((Object)array) != CLASS_ARRAY)
      {
        DXSetError(ERROR_BAD_CLASS, "data component of \"field1\" should be an array");
        goto error;
      }
    }

    /* 
     * get the dependency of the data component
     */
    attr = DXGetAttribute((Object)array, "dep");
    if (! attr)
    {
      DXSetError(ERROR_MISSING_DATA, "data component of \"field1\" has no dependency");
      goto error;
    }

    if (DXGetObjectClass(attr) != CLASS_STRING)
    {
      DXSetError(ERROR_BAD_CLASS, "dependency attribute of data component of \"field1\"");
      goto error;
    }


    DXGetArrayInfo(array, &in_knt[0], &type, &category, &rank, &shape);
    if (type != TYPE_FLOAT || category != CATEGORY_REAL ||
        rank != 0)
    {
      DXSetError(ERROR_DATA_INVALID, "input \"field1\"");
      goto error;
    }

    in_data[0] = DXGetArrayData(array);
    if (! in_data[0])
      goto error;

  }
  /*
   * If the input argument is not NULL then we get the 
   * data array: either the object itself, if its an 
   * array, or the data component if the argument is a field
   */
  if (! in[1])
  {
    array = NULL;
    in_data[1] = NULL;
    in_knt[1] = 0;
  }
  else
  {
    if (DXGetObjectClass(in[1]) == CLASS_ARRAY)
    {
      array = (Array)in[1];
    }
    else
    {
      if (DXGetObjectClass(in[1]) != CLASS_FIELD)
      {
        DXSetError(ERROR_BAD_CLASS, "\"field2\" should be a field");
        goto error;
      }

      array = (Array)DXGetComponentValue((Field)in[1], "data");
      if (! array)
      {
        DXSetError(ERROR_MISSING_DATA, "\"field2\" has no data component");
        goto error;
      }

      if (DXGetObjectClass((Object)array) != CLASS_ARRAY)
      {
        DXSetError(ERROR_BAD_CLASS, "data component of \"field2\" should be an array");
        goto error;
      }
    }

    /* 
     * get the dependency of the data component
     */
    attr = DXGetAttribute((Object)array, "dep");
    if (! attr)
    {
      DXSetError(ERROR_MISSING_DATA, "data component of \"field2\" has no dependency");
      goto error;
    }

    if (DXGetObjectClass(attr) != CLASS_STRING)
    {
      DXSetError(ERROR_BAD_CLASS, "dependency attribute of data component of \"field2\"");
      goto error;
    }

  /*
   * The dependency of this arg should match input[0].
   */
    if (strcmp(src_dependency, DXGetString((String)attr)))
    {
      DXSetError(ERROR_DATA_INVALID, "data dependency of \"field2\" must match \"field1\"");
      goto error;
    }

    DXGetArrayInfo(array, &in_knt[1], &type, &category, &rank, &shape);
    if (type != TYPE_FLOAT || category != CATEGORY_REAL ||
        rank != 0)
    {
      DXSetError(ERROR_DATA_INVALID, "input \"field2\"");
      goto error;
    }

    in_data[1] = DXGetArrayData(array);
    if (! in_data[1])
      goto error;

  }
  /*
   * Create an output data array typed according to the
   * specification given
   */
  array = DXNewArray(TYPE_FLOAT, CATEGORY_REAL, 0, 0);
  if (! array)
    goto error;

  /*
   * Set the dependency of the array to the same as the first input
   */
  if (src_dependency_attr != NULL)
    if (! DXSetAttribute((Object)array, "dep", src_dependency_attr))
      goto error;

  /*
   * The size and dependency of this output data array will 
   * match that of input[0]
   */
  out_knt[0] = in_knt[0];
  /*
   * Actually allocate the array data space
   */
  if (! DXAddArrayData(array, 0, out_knt[0], NULL))
    goto error;

  /*
   * If the output vector slot is not NULL, then it better be a field, and
   * we'll add the new array to it as its data component (delete any prior
   * data component so that its attributes won't overwrite the new component's)
   * Otherwise, place the new array into the out vector.
   */
  if (out[0])
  {
    if (DXGetObjectClass(out[0]) != CLASS_FIELD)
    {
      DXSetError(ERROR_INTERNAL, "non-field object found in output vector");
      goto error;
    }

    if (DXGetComponentValue((Field)out[0], "data"))
      DXDeleteComponent((Field)out[0], "data");

    if (! DXSetComponentValue((Field)out[0], "data", (Object)array))
      goto error;

  }
  else
    out[0] = (Object)array;
  /*
   * Now get the pointer to the contents of the array
   */
  out_data[0] = DXGetArrayData(array);
  if (! out_data[0])
    goto error;

  /*
   * Call the user's routine.  Check the return code.
   */

   /* create invalid component handles for each input field */
   inv_handle1 = DXCreateInvalidComponentHandle(in[0], NULL, src_dependency);
   inv_handle2 = DXCreateInvalidComponentHandle(in[1], NULL, src_dependency);

   if ((!inv_handle1)||(!inv_handle2))
      goto error;

   /* the loop that actually adds the data components */
   out_ptr = (float *)out_data[0];
   in1_ptr = (float *)in_data[0];
   in2_ptr = (float *)in_data[1];
   for (i=0; i<out_knt[0]; i++) {
      if (DXIsElementValid(inv_handle1, i) &&
          DXIsElementValid(inv_handle2, i)) {
            *out_ptr = *in1_ptr + *in2_ptr;
      }
      else {
         *out_ptr = 0.0;
         DXSetElementInvalid(inv_handle1, i);
      }
      out_ptr++;
      in1_ptr++;
      in2_ptr++;
   }

   /* place the invalid component handle into the output field */
   if (!DXSaveInvalidComponent((Field)out[0], inv_handle1))
       goto error;

   /* delete the handles */
   DXFreeInvalidComponentHandle(inv_handle1);
   DXFreeInvalidComponentHandle(inv_handle2);

   return 1;
error:
   /* delete the handles */
   DXFreeInvalidComponentHandle(inv_handle1);
   DXFreeInvalidComponentHandle(inv_handle2);
   return 0;

}

int
Add2Invalid_worker(
    int field1_knt, float *field1_data,
    int field2_knt, float *field2_data,
    int result_knt, float *result_data)
{
  /*
   * The arguments to this routine are:
   *
   *
   * The following are inputs and therefore are read-only.  The default
   * values are given and should be used if the knt is 0.
   *
   * field1_knt, field1_data:  count and pointer for input "field1"
   *                   no default value given.
   * field2_knt, field2_data:  count and pointer for input "field2"
   *                   no default value given.
   *
   *  The output data buffer(s) are writable.
   *  The output buffer(s) are preallocated based on
   *     the dependency (positions or connections),
   *     the size of the corresponding positions or
   *     connections component in the first input, and
   *     the data type.
   *
   * result_knt, result_data:  count and pointer for output "result"
   */

  /*
   * User's code goes here
   */
  
}
